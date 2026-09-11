#ifndef TABLERO_H
#define TABLERO_H

// cada ficha usa 3 bits: A=0, B=1, C=2, D=3, E=4, F=5
// el 6 es casilla vacia y el 7 no se usa todavia
const unsigned char FICHA_VACIA = 6;
const unsigned char MASCARA_FICHA = 7;
const int TIPOS_FICHA = 6;

int calcularBytes(int filas, int columnas);
unsigned char* crearTablero(int filas, int columnas);

unsigned char leerFicha(unsigned char* tablero, int indice);
void escribirFicha(unsigned char* tablero, int indice, unsigned char valor);

void llenarAleatorio(unsigned char* tablero, int filas, int columnas);

void mostrarFichas(unsigned char* tablero, int filas, int columnas);
void mostrarBinario(unsigned char* tablero, int filas, int columnas);
void mostrarMemoria(unsigned char* tablero, int filas, int columnas);

#endif
