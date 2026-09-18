#ifndef ESTRUCTURA_H
#define ESTRUCTURA_H

void agregarFila(unsigned char* &tablero, int &filas, int columnas, int &capacidad, int posicion);
void eliminarFila(unsigned char* &tablero, int &filas, int columnas, int &capacidad, int posicion);
void agregarColumna(unsigned char* &tablero, int filas, int &columnas, int &capacidad, int posicion);
void eliminarColumna(unsigned char* &tablero, int filas, int &columnas, int &capacidad, int posicion);

#endif
