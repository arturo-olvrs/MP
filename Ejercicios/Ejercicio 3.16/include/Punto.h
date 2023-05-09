/* 
 * @file:   Punto.h
 * @author: Arturo Olivares Martos <2004.olivares@gmail.com>
 *
 * @date 2 de Mayo de 2023, 1:20 PM
 */

#ifndef PUNTO_H
#define PUNTO_H

#include <iostream> // ifstream

class Punto {
public:
    Punto();
    Punto(double x, double y);
    
    double getX() const;
    double getY() const;
    
    void setXY (double x, double y);
    
    double getDistance (const Punto& otro) const;
    
    void mostrar (std::ostream& flujo) const;
    
    void leer (std::istream& flujo);
    
private:
    double _x,_y;
};

#endif /* PUNTO_H */

