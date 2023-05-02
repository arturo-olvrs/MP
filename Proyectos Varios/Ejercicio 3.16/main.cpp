/* 
 * @file:   main.cpp
 * @author: Arturo Olivares Martos <2004.olivares@gmail.com>
 * @brief Ejercicio 14 de la relación 3.
 *
 * @date 2 de Mayo de 2023, 1:20 PM
 */

#include <iostream>
#include <fstream> // ifstream

#include "Punto.h"
#include "Poligono.h"
using namespace std;


int main(int argc, char* argv[]) {
    
    Poligono pol;
    
    if (argc==1)
        pol.leer(cin);
    
    else {
        ifstream flujo;
        flujo.open(argv[1]);
        if (!flujo) {
            cerr << "Error: Fichero " << argv[1] << " no válido." << endl;
            return 1;
        }
        pol.leer(flujo);
        flujo.close();
    }
    
    std::cout << "\nEl poligono introducido es:" << std::endl;
    pol.mostrar(cout);
    
    
    cout << std::endl << std::endl;
    cout << "\tArea = " << pol.getArea() << std::endl;
    cout << "\tPerimetro = " << pol.getPerimetro() << std::endl;
    
    
    pol.liberar(); // Libera la memoria dinámica reservada
}
