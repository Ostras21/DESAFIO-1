#include <cstdlib>
#include "tablero.h"
#include "juego.h"

void eliminarFicha(unsigned char* tablero, int columnas, int fila, int columna)
{
    escribirFicha(tablero, fila * columnas + columna, FICHA_VACIA);
}

// cada columna se recorre de abajo hacia arriba, f va leyendo y escribir dice
// en que posicion va la siguiente ficha que no esta vacia
void bajarFichas(unsigned char* tablero, int filas, int columnas)
{
    for (int c = 0; c < columnas; c++) {
        int escribir = filas - 1;

        for (int f = filas - 1; f >= 0; f--) {
            unsigned char ficha = leerFicha(tablero, f * columnas + c);
            if (ficha != FICHA_VACIA) {
                if (f != escribir) {
                    escribirFicha(tablero, escribir * columnas + c, ficha);
                }
                escribir--;
            }
        }

        // lo que queda arriba son los huecos
        for (int f = escribir; f >= 0; f--) {
            escribirFicha(tablero, f * columnas + c, FICHA_VACIA);
        }
    }
}

void rellenarVacias(unsigned char* tablero, int filas, int columnas)
{
    int total = filas * columnas;
    for (int i = 0; i < total; i++) {
        if (leerFicha(tablero, i) == FICHA_VACIA) {
            escribirFicha(tablero, i, rand() % TIPOS_FICHA);
        }
    }
}
