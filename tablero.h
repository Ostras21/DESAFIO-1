#ifndef TABLERO_H
#define TABLERO_H

// Cada ficha ocupa 3 bits dentro del tablero
// 000 = A, 001 = B, 010 = C, 011 = D, 100 = E, 101 = F
// 110 = casilla vacia
// 111 = no se usa por ahora
const unsigned char FICHA_VACIA = 6;
const unsigned char MASCARA_FICHA = 7;   // 0000 0111
const int TIPOS_FICHA = 6;

int calcularBytes(int filas, int columnas);
unsigned char* crearTablero(int filas, int columnas);

unsigned char leerFicha(unsigned char* tablero, int indice);
void escribirFicha(unsigned char* tablero, int indice, unsigned char valor);

void llenarAleatorio(unsigned char* tablero, int filas, int columnas);

void mostrarFichas(unsigned char* tablero, int filas, int columnas);
void mostrarBinario(unsigned char* tablero, int filas, int columnas);
void mostrarMemoria(unsigned char* tablero, int filas, int columnas);

#endif // TABLERO_H
