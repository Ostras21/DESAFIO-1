#include <iostream>
#include <cstdlib>
#include <ctime>
#include "tablero.h"
#include "juego.h"

using namespace std;

// pide un numero hasta que el usuario escriba uno dentro del rango
int leerEntero(int minimo, int maximo)
{
    int valor = minimo - 1;

    do {
        cin >> valor;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            valor = minimo - 1;
        }
        if (valor < minimo || valor > maximo) {
            cout << "Valor no valido, intente de nuevo: ";
        }
    } while (valor < minimo || valor > maximo);

    return valor;
}

int main()
{
    srand(time(0));

    cout << "SWEET CRUSH" << endl << endl;

    // minimo 3 para que se puedan hacer combinaciones
    cout << "Numero de filas (3 a 30): ";
    int filas = leerEntero(3, 30);

    cout << "Numero de columnas (3 a 30): ";
    int columnas = leerEntero(3, 30);

    unsigned char* tablero = crearTablero(filas, columnas);
    llenarAleatorio(tablero, filas, columnas);

    int eliminaciones = 0;
    int fichasEliminadas = 0;
    int combinaciones = 0;
    int cascadas = 0;
    int puntaje = 0;

    // el tablero puede salir con combinaciones desde el principio,
    // se resuelven antes de empezar y no cuentan para el puntaje
    procesarCascadas(tablero, filas, columnas, combinaciones, fichasEliminadas, puntaje);
    combinaciones = 0;
    fichasEliminadas = 0;
    puntaje = 0;

    int opcion = 0;

    do {
        mostrarFichas(tablero, filas, columnas);
        mostrarBinario(tablero, filas, columnas);

        cout << endl;
        cout << "1. Eliminar una ficha" << endl;
        cout << "2. Ver la memoria" << endl;
        cout << "3. Ver estadisticas" << endl;
        cout << "0. Salir" << endl;
        cout << "Opcion: ";
        opcion = leerEntero(0, 3);

        if (opcion == 1) {
            cout << "Fila (0 a " << filas - 1 << "): ";
            int fila = leerEntero(0, filas - 1);

            cout << "Columna (0 a " << columnas - 1 << "): ";
            int columna = leerEntero(0, columnas - 1);

            eliminarFicha(tablero, columnas, fila, columna);
            bajarFichas(tablero, filas, columnas);
            rellenarVacias(tablero, filas, columnas);

            eliminaciones++;
            fichasEliminadas++;

            cascadas = procesarCascadas(tablero, filas, columnas,
                                        combinaciones, fichasEliminadas, puntaje);

            cout << endl << "Cascadas en esta jugada: " << cascadas << endl;
        }

        if (opcion == 2) {
            mostrarMemoria(tablero, filas, columnas);
        }

        if (opcion == 3) {
            cout << endl;
            cout << "Tablero: " << filas << " x " << columnas << endl;
            cout << "Eliminaciones del usuario: " << eliminaciones << endl;
            cout << "Fichas eliminadas: " << fichasEliminadas << endl;
            cout << "Combinaciones: " << combinaciones << endl;
            cout << "Cascadas de la ultima jugada: " << cascadas << endl;
            cout << "Puntaje: " << puntaje << endl;
        }

    } while (opcion != 0);

    delete[] tablero;
    tablero = nullptr;

    return 0;
}
