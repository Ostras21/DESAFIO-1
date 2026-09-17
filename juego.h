#ifndef JUEGO_H
#define JUEGO_H

void eliminarFicha(unsigned char* tablero, int columnas, int fila, int columna);
void bajarFichas(unsigned char* tablero, int filas, int columnas);
void rellenarVacias(unsigned char* tablero, int filas, int columnas);

int bytesMarcas(int filas, int columnas);
int marcarCombinaciones(unsigned char* tablero, int filas, int columnas, unsigned char* marcas);
int eliminarMarcadas(unsigned char* tablero, int filas, int columnas, unsigned char* marcas);
int procesarCascadas(unsigned char* tablero, int filas, int columnas,
                     int &combinaciones, int &fichasEliminadas, int &puntaje);

#endif
