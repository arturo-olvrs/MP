/* 
 * @file:   Punto.cpp
 * @author: Arturo Olivares Martos <2004.olivares@gmail.com>
 *
 * @date 2 de Mayo de 2023, 1:20 PM
 */

#include <math.h>
#include <fstream> // ifstream
#include "Punto.h"


Punto::Punto():
    _x(0), _y(0)
{}

Punto::Punto(double x, double y):
    _x(x), _y(y)
{}

double Punto::getX() const{
    return _x;
}
double Punto::getY() const{
    return _y;
}

void Punto::setXY (double x, double y){
    _x = x;
    _y = y;
}

double Punto::getDistance (const Punto& otro) const{
    
    double dif_coord_x = _x - otro._x;
    double dif_coord_y = _y - otro._y;
    
    return sqrt(dif_coord_x*dif_coord_x + dif_coord_y*dif_coord_y);
}


void Punto::mostrar (std::ostream& flujo) const{
    
    flujo << _x << " " << _y << std::endl;
}


void Punto::leer (std::istream& flujo){
        
    flujo >> _x >> _y;
}