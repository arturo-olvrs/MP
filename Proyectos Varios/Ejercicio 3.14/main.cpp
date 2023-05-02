/* 
 * @file:   main.cpp
 * @author: Arturo Olivares Martos <2004.olivares@gmail.com>
 * @brief Ejercicio 14 de la relación 3.
 *
 * @date 2 de Mayo de 2023, 1:20 PM
 */

#include <iostream>
#include <fstream> // ifstream

#include "VectorDinamicoChar.h"
using namespace std;


int main(int argc, char* argv[]) {
    
    VectorDinamicoChar arrayChar;
    
    if (argc==1)
        arrayChar.leer(cin);
    
    else {
        ifstream flujo;
        flujo.open(argv[1]);
        if (!flujo) {
            cerr << "Error: Fichero " << argv[1] << " no válido." << endl;
            return 1;
        }
        arrayChar.leer(flujo);
        flujo.close();
    }
    
    arrayChar.mostrar(cout);
    arrayChar.liberar(); // Libera la memoria dinámica reservada
}
