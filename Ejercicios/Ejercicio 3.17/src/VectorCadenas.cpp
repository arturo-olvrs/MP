/* 
 * @file:   VectorCadenas.cpp
 * @author: Arturo Olivares Martos <2004.olivares@gmail.com>
 *
 * @date 4 de Mayo de 2023, 1:20 PM
 */

#include <cstring>
#include <iostream>
#include "VectorCadenas.h"

using namespace std;

void VectorCadenas::inicializar(int capacidad){
    
    // Reservo memoria para el array
    _cadenas = new char* [capacidad];
    
    // Reservo memoria para cada cadena
    for (int i=0; i<capacidad; i++)
        _cadenas[i] = new char[NCARACTERES];
        
    _ncads = 0;
    _capacidad = capacidad;
}

VectorCadenas::VectorCadenas(){
    inicializar();
}

void VectorCadenas::liberar(){
    
    // Primero libero cada cadena
    for (int i=0; i<_capacidad; i++)
        delete[] _cadenas[i];
    
    // Libero el array
    delete [] _cadenas;
    _cadenas = nullptr;
    _ncads = 0;
    _capacidad = 0;
}

void VectorCadenas::clear(){
    liberar();
    inicializar();
}

void VectorCadenas::redimensionar (int newSize){
    
    if (newSize < _capacidad){
        
        std::string err;
        err += "void VectorCadenas::redimensionar (int newSize)\n";
        err += "newSize must be >= _capacidad";
        
        throw std::invalid_argument (err);
    }
    
    char** aux = new char* [newSize];
    
    for(int i=0; i<_ncads; i++)
        aux[i] = _cadenas[i];
    
    delete[] _cadenas;
    _cadenas = aux;
    _capacidad = newSize;
}

void VectorCadenas::aniadir (const char* cadena){
    
    if (_ncads >= _capacidad)
        redimensionar(2*_capacidad);
    
    strcpy(_cadenas[_ncads], cadena);
    _ncads ++;
}

void VectorCadenas::leer(std::istream& flujo){
    
    char linea[NCARACTERES];
    
    clear();
    
    while (flujo.getline(linea, NCARACTERES))
        aniadir(linea);
}

void VectorCadenas::mostrar(std::ostream& flujo) const{
    
    for (int i=0; i<_ncads; i++){
        
        // Se muestra cada cadena
        int pos=0;
        while (_cadenas[i][pos] != '\0'){
            flujo << _cadenas[i][pos];
            pos ++;
        }
        flujo << std::endl;
    }
}

void VectorCadenas::ordenar(int (*comparar) (const char*, const char*)){
    
    // Método de ordenación mediante selección
    int min;
    char aux[NCARACTERES]; // Para intercambiar
    for (int left=0; left<_ncads; left++){
        
        min = left;
        for (int i=left+1; i<_ncads; i++){
            if ( (*comparar)(_cadenas[min], _cadenas[i]) >= 0 )
                min = i;
        }
        
        // Intercambio
        char* aux = _cadenas[min];
        _cadenas[min]=_cadenas[left];
        _cadenas[left]=aux;
        
        /* Esto no es correcto. Intercambia los valores, no las direcciones de memoria
        strcpy(aux,_cadenas[min_o_max]);
        strcpy(_cadenas[min_o_max], _cadenas[left]);
        strcpy(_cadenas[left], aux);
        */
    }
}