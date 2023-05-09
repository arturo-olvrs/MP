/* 
 * @file:   main.cpp
 * @author: Arturo Olivares Martos <2004.olivares@gmail.com>
 * @brief Ejercicio 17 de la relación 3.
 *
 * @date 4 de Mayo de 2023, 1:20 PM
 */

#include <iostream>
#include <fstream> // ifstream
#include <cstring>

#include "VectorCadenas.h"
using namespace std;


int main(int argc, char* argv[]) {
    
    VectorCadenas vCadenas;
    
    if (argc==1)
        vCadenas.leer(cin);
    
    else {
        ifstream flujo;
        flujo.open(argv[1]);
        if (!flujo) {
            cerr << "Error: Fichero " << argv[1] << " no válido." << endl;
            return 1;
        }
        vCadenas.leer(flujo);
        flujo.close();
    }
    
    std::cout << "\nOriginal:" << std::endl;
    vCadenas.mostrar(cout);
    
    vCadenas.ordenar(strcmp);
    
    cout << "\n\nResultado:" << std::endl;
    vCadenas.mostrar(cout);
    
    
    vCadenas.liberar(); // Libera la memoria dinámica reservada
}
