/* 
 * @file:   VectorDinamicoChar.cpp
 * @author: Arturo Olivares Martos <2004.olivares@gmail.com>
 *
 * @date 2 de Mayo de 2023, 1:20 PM
 */

#include <string>
#include "VectorDinamicoChar.h"

#include <iostream> // ifstream


VectorDinamicoChar::VectorDinamicoChar(int capacidad){
    
    inicializar(capacidad);
    
}

VectorDinamicoChar::VectorDinamicoChar(){
    
    inicializar();
    
}
    

void VectorDinamicoChar::inicializar(int capacidad){
    
    _arrayChar = new char[capacidad];
    _nCaracteres = 0;
    _capacidad = capacidad;
    
}
void VectorDinamicoChar::liberar(){
    
    delete [] _arrayChar;
    _arrayChar = nullptr;
    _capacidad = 0;
    _nCaracteres = 0;
}

void VectorDinamicoChar::clear(){
    liberar();
    inicializar();
}

void VectorDinamicoChar::redimensionar (){
    
    int incremento = _capacidad;
    
    // Reservo memoria para el array con el nuevo tamaño
    char* arr_ampliado = new char[_capacidad + incremento];
    
    // Copio el array en arr_ampliado:
    for (int i=0; i<_nCaracteres; i++)
        arr_ampliado[i] = _arrayChar[i];
    
    delete [] _arrayChar;
    _arrayChar = arr_ampliado;
    _capacidad = _capacidad + incremento;
}

void VectorDinamicoChar::aniadir (char caracter){
    
    while (_nCaracteres >= _capacidad)
        redimensionar();
   
    _arrayChar[_nCaracteres] = caracter;
    _nCaracteres ++;
}

void VectorDinamicoChar::mostrar (std::ostream& flujo) const{
    
    for (int i=0; i<_nCaracteres; i++)
        flujo << _arrayChar[i];
}

void VectorDinamicoChar::leer(std::istream& flujo){
    
    char caracter;
    
    clear();
    
    while(flujo.get(caracter))
        aniadir (caracter);
    
}