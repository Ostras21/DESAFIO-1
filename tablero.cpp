#include <iostream>
#include <cstdlib>
#include "tablero.h"

using namespace std;

// Bytes minimos para guardar filas*columnas fichas de 3 bits.
// Se suma 7 antes de dividir entre 8 para redondear hacia arriba.
int calcularBytes(int filas, int columnas)
{
    int totalBits = filas * columnas * 3;
    return (totalBits + 7) >> 3;
}

unsigned char* crearTablero(int filas, int columnas)
{
    int bytes = calcularBytes(filas, columnas);
    unsigned char* tablero = new unsigned char[bytes];

    // se deja todo en cero para que los bits que sobran queden limpios
    for (int i = 0; i < bytes; i++) {
        tablero[i] = 0;
    }
    return tablero;
}

// La ficha numero "indice" empieza en el bit indice*3 de toda la trama.
// El bit 0 de la trama es el bit menos significativo del byte 0,
// el bit 8 es el menos significativo del byte 1, y asi.
unsigned char leerFicha(unsigned char* tablero, int indice)
{
    int bitInicio = indice * 3;
    int numByte = bitInicio >> 3;   // lo mismo que dividir entre 8
    int posBit = bitInicio & 7;     // lo mismo que el residuo de dividir entre 8

    unsigned char valor = tablero[numByte] >> posBit;

    // si la ficha empieza en el bit 6 o 7 no cabe en este byte,
    // los bits que faltan estan al principio del siguiente byte
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

    // primero se borran los 3 bits que habia y despues se ponen los nuevos
    tablero[numByte] = (tablero[numByte] & ~(MASCARA_FICHA << posBit)) | (valor << posBit);

    // parte que queda en el siguiente byte (1 o 2 bits)
    if (posBit > 5) {
        int bitsQueFaltan = posBit - 5;
        unsigned char mascara = (1 << bitsQueFaltan) - 1;   // 0000 0001 o 0000 0011
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

// Muestra el codigo de 3 bits de cada ficha en su posicion del tablero
void mostrarBinario(unsigned char* tablero, int filas, int columnas)
{
    cout << endl << "Tablero en binario (3 bits por ficha):" << endl;
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

// Muestra los bytes tal como estan en memoria.
// Se imprimen del ultimo byte al primero para que el bit menos
// significativo de toda la trama quede a la derecha y los bits
// que sobran (siempre en cero) queden a la izquierda.
void mostrarMemoria(unsigned char* tablero, int filas, int columnas)
{
    int bytes = calcularBytes(filas, columnas);

    cout << endl << "Memoria usada: " << bytes << " bytes ("
         << filas * columnas * 3 << " bits validos)" << endl;

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
