#include <iostream>
#include <cstdlib>
#include "tablero.h"

using namespace std;

int calcularBytes(int filas, int columnas)
{
    int totalBits = filas * columnas * 3;
    // se suma 7 para redondear hacia arriba
    return (totalBits + 7) >> 3;
}

unsigned char* crearTablero(int filas, int columnas)
{
    int bytes = calcularBytes(filas, columnas);
    unsigned char* tablero = new unsigned char[bytes];

    for (int i = 0; i < bytes; i++) {
        tablero[i] = 0;
    }
    return tablero;
}

// la ficha empieza en el bit indice*3 contando desde el bit 0 del byte 0
unsigned char leerFicha(unsigned char* tablero, int indice)
{
    int bitInicio = indice * 3;
    int numByte = bitInicio >> 3;
    int posBit = bitInicio & 7;

    unsigned char valor = tablero[numByte] >> posBit;

    // si empieza en el bit 6 o 7 una parte queda en el siguiente byte
    if (posBit > 5) {
        valor = valor | (tablero[numByte + 1] << (8 - posBit));
    }

    return valor & MASCARA_FICHA;
}

void escribirFicha(unsigned char* tablero, int indice, unsigned char valor)
{
    int bitInicio = indice * 3;
    int numByte = bitInicio >> 3;
    int posBit = bitInicio & 7;

    valor = valor & MASCARA_FICHA;

    // se limpian los 3 bits y luego se ponen los nuevos
    tablero[numByte] = (tablero[numByte] & ~(MASCARA_FICHA << posBit)) | (valor << posBit);

    if (posBit > 5) {
        int bitsQueFaltan = posBit - 5;
        unsigned char mascara = (1 << bitsQueFaltan) - 1;
        tablero[numByte + 1] = (tablero[numByte + 1] & ~mascara) | (valor >> (8 - posBit));
    }
}

void llenarAleatorio(unsigned char* tablero, int filas, int columnas)
{
    int total = filas * columnas;
    for (int i = 0; i < total; i++) {
        escribirFicha(tablero, i, rand() % TIPOS_FICHA);
    }
}

void mostrarFichas(unsigned char* tablero, int filas, int columnas)
{
    char simbolos[8] = {'A', 'B', 'C', 'D', 'E', 'F', '.', '*'};

    cout << endl << "    ";
    for (int c = 0; c < columnas; c++) {
        if (c < 10) cout << " ";
        cout << c << " ";
    }
    cout << endl;

    for (int f = 0; f < filas; f++) {
        if (f < 10) cout << " ";
        cout << f << "  ";
        for (int c = 0; c < columnas; c++) {
            unsigned char ficha = leerFicha(tablero, f * columnas + c);
            cout << " " << simbolos[ficha] << " ";
        }
        cout << endl;
    }
}

void mostrarBinario(unsigned char* tablero, int filas, int columnas)
{
    cout << endl << "Tablero en binario:" << endl;
    for (int f = 0; f < filas; f++) {
        for (int c = 0; c < columnas; c++) {
            unsigned char ficha = leerFicha(tablero, f * columnas + c);
            for (int b = 2; b >= 0; b--) {
                cout << ((ficha >> b) & 1);
            }
            cout << " ";
        }
        cout << endl;
    }
}

// se imprime desde el ultimo byte para que los bits que sobran queden a la izquierda
void mostrarMemoria(unsigned char* tablero, int filas, int columnas)
{
    int bytes = calcularBytes(filas, columnas);

    cout << endl << "Memoria: " << bytes << " bytes, "
         << filas * columnas * 3 << " bits usados" << endl;

    int contador = 0;
    for (int i = bytes - 1; i >= 0; i--) {
        for (int b = 7; b >= 0; b--) {
            cout << ((tablero[i] >> b) & 1);
        }
        cout << " ";
        contador++;
        if (contador % 8 == 0) {
            cout << endl;
        }
    }
    cout << endl;
}
