/* 
 * @file:   Poligono.cpp
 * @author: Arturo Olivares Martos <2004.olivares@gmail.com>
 *
 * @date 2 de Mayo de 2023, 1:20 PM
 */

#include <fstream> // ifstream

#include "Punto.h"
#include "Poligono.h"

Poligono::Poligono(){
    
    inicializar();
}

Poligono::Poligono(int n){
    
    inicializar(n);
}

void Poligono::inicializar(int n){
    if (n < 0){
        
        std::string err;
        err += "Poligono(int n)\n";
        err += "n must be >= 0";
        
        throw std::invalid_argument (err);
    }
    
    _vertices = new Punto[n];
    _nVertices = 0;
    _capacidad = n;
}

void Poligono::liberar(){
    
    delete[] _vertices;
    _vertices = nullptr;
    _nVertices = 0;
    _capacidad = 0;
}

void Poligono::clear(){
    
    liberar();
    inicializar();
}

int Poligono::getNumeroVertices() const{
    return _nVertices;
}
Punto Poligono::getVertice(int index) const{
    if (index < 0 || index >= _nVertices){
        
        std::string err;
        err += "Punto Poligono::getVertice(int index) const\n";
        err += "Index must be 0 <= index< _nVertices";
        
        throw std::out_of_range (err);
    }
    
    return _vertices[index];
}


void Poligono::redimensionar(int incremento){
    
    Punto* arr_aux = new Punto[_capacidad + incremento];
    
    for (int i=0; i<_nVertices; i++)
        arr_aux[i]=_vertices[i];
    
    delete [] _vertices;
    _vertices = arr_aux;
    
    _capacidad += incremento;
}



void Poligono::addVertice(const Punto& v){
    
    if (_nVertices == _capacidad)
        redimensionar(_capacidad);
        
    _vertices[_nVertices] = v;
    _nVertices ++;
}

/**
 * Función que calcula el perímetro de un polígono
 * @return El perímetro del polígono
 * @pre Los puntos deben estar en puestos adyacentes. No se comprueba.
 */
double Poligono::getPerimetro() const{
    
    double dist = 0;
    
    for (int i=0; i<_nVertices; i++)
        dist += _vertices[i].getDistance(_vertices[(i+1)%_nVertices]);
    
    return dist;
}

double Poligono::getArea() const{
    
    double area=0;
    
    Punto p1, p2;
    Punto pInt = getPuntoInterior();
    
    for (int i=0; i<_nVertices; i++){
        
        p1 = _vertices[i];
        p2 = _vertices[(i+1)%_nVertices];
        
        area += areaTriangulo(p1,p2,pInt);
    }
    
    return (area);
}


Punto Poligono::getPuntoInterior() const{
    
    return _vertices[0];
}

void Poligono::mostrar (std::ostream& flujo) const{
    
    flujo << _nVertices << std::endl;
    
    for (int i=0; i<_nVertices; i++)
        _vertices[i].mostrar(flujo);
}

void Poligono::leer (std::istream& flujo){
    
    clear();
    
    int numVertices;
    
    flujo >> numVertices;
    Punto a_aniadir;
    
    for (int i=0; i<numVertices; i++){
        a_aniadir.leer(flujo);
        addVertice(a_aniadir);
    }
    
}


double areaTriangulo (const Punto& p1, const Punto& p2, const Punto& p3){
    
    double S_1 = p1.getDistance(p2);
    double S_2 = p2.getDistance(p3);
    double S_3 = p3.getDistance(p1);
    
    double T = (S_1+S_2+S_3)/2.0;
    
    double prod = T*(T-S_1)*(T-S_2)*(T-S_3);
    
    return sqrt(prod);
}