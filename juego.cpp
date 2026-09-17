#include <cstdlib>
#include "tablero.h"
#include "juego.h"

// las marcas son un bit por casilla, solo se usan mientras se procesa una jugada
void marcar(unsigned char* marcas, int indice)
{
    marcas[indice >> 3] = marcas[indice >> 3] | (1 << (indice & 7));
}

int estaMarcada(unsigned char* marcas, int indice)
{
    return (marcas[indice >> 3] >> (indice & 7)) & 1;
}

int bytesMarcas(int filas, int columnas)
{
    return (filas * columnas + 7) >> 3;
}

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

// busca tramos de 3 o mas fichas iguales seguidas y los marca.
// primero las filas y despues las columnas, asi una ficha que esta en las dos
// solo queda marcada una vez. devuelve cuantas combinaciones encontro
int marcarCombinaciones(unsigned char* tablero, int filas, int columnas, unsigned char* marcas)
{
    int bytes = bytesMarcas(filas, columnas);
    for (int i = 0; i < bytes; i++) {
        marcas[i] = 0;
    }

    int combinaciones = 0;

    for (int f = 0; f < filas; f++) {
        int inicio = 0;
        while (inicio < columnas) {
            unsigned char ficha = leerFicha(tablero, f * columnas + inicio);
            int fin = inicio + 1;
            while (fin < columnas && leerFicha(tablero, f * columnas + fin) == ficha) {
                fin++;
            }
            if (ficha != FICHA_VACIA && fin - inicio >= 3) {
                for (int c = inicio; c < fin; c++) {
                    marcar(marcas, f * columnas + c);
                }
                combinaciones++;
            }
            inicio = fin;
        }
    }

    for (int c = 0; c < columnas; c++) {
        int inicio = 0;
        while (inicio < filas) {
            unsigned char ficha = leerFicha(tablero, inicio * columnas + c);
            int fin = inicio + 1;
            while (fin < filas && leerFicha(tablero, fin * columnas + c) == ficha) {
                fin++;
            }
            if (ficha != FICHA_VACIA && fin - inicio >= 3) {
                for (int f = inicio; f < fin; f++) {
                    marcar(marcas, f * columnas + c);
                }
                combinaciones++;
            }
            inicio = fin;
        }
    }

    return combinaciones;
}

int eliminarMarcadas(unsigned char* tablero, int filas, int columnas, unsigned char* marcas)
{
    int total = filas * columnas;
    int eliminadas = 0;

    for (int i = 0; i < total; i++) {
        if (estaMarcada(marcas, i)) {
            escribirFicha(tablero, i, FICHA_VACIA);
            eliminadas++;
        }
    }

    return eliminadas;
}

// repite marcar, eliminar, bajar y rellenar mientras sigan saliendo combinaciones.
// cada vuelta es una cascada y vale mas puntos que la anterior
int procesarCascadas(unsigned char* tablero, int filas, int columnas,
                     int &combinaciones, int &fichasEliminadas, int &puntaje)
{
    unsigned char* marcas = new unsigned char[bytesMarcas(filas, columnas)];

    int cascadas = 0;
    int encontradas = marcarCombinaciones(tablero, filas, columnas, marcas);

    while (encontradas > 0) {
        cascadas++;
        combinaciones += encontradas;

        int eliminadas = eliminarMarcadas(tablero, filas, columnas, marcas);
        fichasEliminadas += eliminadas;
        puntaje += eliminadas * 10 * cascadas;

        bajarFichas(tablero, filas, columnas);
        rellenarVacias(tablero, filas, columnas);

        encontradas = marcarCombinaciones(tablero, filas, columnas, marcas);
    }

    delete[] marcas;
    marcas = nullptr;

    return cascadas;
}
