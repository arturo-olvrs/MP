/* 
 * @file:   Poligono.h
 * @author: Arturo Olivares Martos <2004.olivares@gmail.com>
 *
 * @date 2 de Mayo de 2023, 1:20 PM
 */

#include "Punto.h"
#include <math.h>
#include <fstream> // ifstream

#ifndef POLIGONO_H
#define POLIGONO_H

class Poligono {
public:
    Poligono();
    Poligono(int n);
    
    void liberar();
    void redimensionar(int incremento);
    
    int getNumeroVertices() const;
    Punto getVertice(int index) const;
    
    void addVertice(const Punto& v);
    
    double getPerimetro() const;
    
    double getArea() const;
    
    void mostrar (std::ostream& flujo) const;
    void leer (std::istream& flujo);
    
private:
    void inicializar(int n=4);
    void clear();
    
    Punto getPuntoInterior() const;
    
private:
    int _nVertices;      // Número de puntos en el array dinámico
    int _capacidad;      // Cantidad de memoria reservada
    Punto* _vertices;    // Array dinámico de objetos Punto
};


double areaTriangulo (const Punto& p1, const Punto& p2, const Punto& p3);

#endif /* POLIGONO_H */

