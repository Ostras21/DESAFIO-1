#include <iostream>
#include <cstdlib>
#include <ctime>
#include "tablero.h"

using namespace std;

int main()
{
    srand(time(0));

    int filas = 0;
    int columnas = 0;

    cout << "SWEET CRUSH" << endl << endl;

    // minimo 3 para que se puedan hacer combinaciones
    do {
        cout << "Numero de filas (3 a 30): ";
        cin >> filas;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            filas = 0;
        }
        if (filas < 3 || filas > 30) {
            cout << "Valor no valido" << endl;
        }
    } while (filas < 3 || filas > 30);

    do {
        cout << "Numero de columnas (3 a 30): ";
        cin >> columnas;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            columnas = 0;
        }
        if (columnas < 3 || columnas > 30) {
            cout << "Valor no valido" << endl;
        }
    } while (columnas < 3 || columnas > 30);

    unsigned char* tablero = crearTablero(filas, columnas);
    llenarAleatorio(tablero, filas, columnas);

    mostrarFichas(tablero, filas, columnas);
    mostrarBinario(tablero, filas, columnas);
    mostrarMemoria(tablero, filas, columnas);

    delete[] tablero;
    tablero = nullptr;

    return 0;
}
