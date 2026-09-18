#include <cstdlib>
#include "tablero.h"
#include "estructura.h"

// si el tablero nuevo no cabe en lo que hay reservado se pide un bloque del
// tamaño exacto, se copian los bytes y se libera el viejo
void asegurarCapacidad(unsigned char* &tablero, int &capacidad, int bytesNecesarios)
{
    if (bytesNecesarios <= capacidad) {
        return;
    }

    unsigned char* nuevo = new unsigned char[bytesNecesarios];

    for (int i = 0; i < capacidad; i++) {
        nuevo[i] = tablero[i];
    }
    for (int i = capacidad; i < bytesNecesarios; i++) {
        nuevo[i] = 0;
    }

    delete[] tablero;
    tablero = nuevo;
    capacidad = bytesNecesarios;
}

// solo se achica la memoria cuando se esta usando menos del 65 % de lo reservado.
// se compara con enteros (por 100 y por 65) para no usar decimales
void reducirCapacidad(unsigned char* &tablero, int &capacidad, int bytesNecesarios)
{
    if (bytesNecesarios * 100 >= capacidad * 65) {
        return;
    }

    unsigned char* nuevo = new unsigned char[bytesNecesarios];

    for (int i = 0; i < bytesNecesarios; i++) {
        nuevo[i] = tablero[i];
    }

    delete[] tablero;
    tablero = nuevo;
    capacidad = bytesNecesarios;
}

// deja en cero las fichas que ya no hacen parte del tablero
void limpiarSobrantes(unsigned char* tablero, int desde, int hasta)
{
    for (int i = desde; i < hasta; i++) {
        escribirFicha(tablero, i, 0);
    }
}

void agregarFila(unsigned char* &tablero, int &filas, int columnas, int &capacidad, int posicion)
{
    int viejas = filas * columnas;
    asegurarCapacidad(tablero, capacidad, calcularBytes(filas + 1, columnas));

    // se empieza por la ultima ficha para no pisar las que faltan por mover
    for (int i = viejas - 1; i >= posicion * columnas; i--) {
        escribirFicha(tablero, i + columnas, leerFicha(tablero, i));
    }

    for (int c = 0; c < columnas; c++) {
        escribirFicha(tablero, posicion * columnas + c, rand() % TIPOS_FICHA);
    }

    filas++;
}

void eliminarFila(unsigned char* &tablero, int &filas, int columnas, int &capacidad, int posicion)
{
    int viejas = filas * columnas;
    int nuevas = (filas - 1) * columnas;

    // aqui se va hacia adelante porque cada ficha queda en una posicion anterior
    for (int i = posicion * columnas; i < nuevas; i++) {
        escribirFicha(tablero, i, leerFicha(tablero, i + columnas));
    }

    limpiarSobrantes(tablero, nuevas, viejas);
    filas--;

    reducirCapacidad(tablero, capacidad, calcularBytes(filas, columnas));
}

void agregarColumna(unsigned char* &tablero, int filas, int &columnas, int &capacidad, int posicion)
{
    asegurarCapacidad(tablero, capacidad, calcularBytes(filas, columnas + 1));

    // al haber una columna mas todas las fichas se corren hacia el final,
    // por eso se recorre desde la ultima
    for (int f = filas - 1; f >= 0; f--) {
        for (int c = columnas - 1; c >= 0; c--) {
            int destino = c;
            if (c >= posicion) {
                destino = c + 1;
            }
            escribirFicha(tablero, f * (columnas + 1) + destino, leerFicha(tablero, f * columnas + c));
        }
    }

    for (int f = 0; f < filas; f++) {
        escribirFicha(tablero, f * (columnas + 1) + posicion, rand() % TIPOS_FICHA);
    }

    columnas++;
}

void eliminarColumna(unsigned char* &tablero, int filas, int &columnas, int &capacidad, int posicion)
{
    int viejas = filas * columnas;

    for (int f = 0; f < filas; f++) {
        for (int c = 0; c < columnas; c++) {
            if (c != posicion) {
                int destino = c;
                if (c > posicion) {
                    destino = c - 1;
                }
                escribirFicha(tablero, f * (columnas - 1) + destino, leerFicha(tablero, f * columnas + c));
            }
        }
    }

    columnas--;
    limpiarSobrantes(tablero, filas * columnas, viejas);

    reducirCapacidad(tablero, capacidad, calcularBytes(filas, columnas));
}
