/* 
 * @file:   VectorCadenas.h
 * @author: Arturo Olivares Martos <2004.olivares@gmail.com>
 *
 * @date 4 de Mayo de 2023, 1:20 PM
 */

#ifndef VECTORCADENAS_H
#define VECTORCADENAS_H

#include <fstream> // ifstream

class VectorCadenas {
public:
    
    VectorCadenas();
    
    void liberar();
    void clear();
    
    void redimensionar (int newSize);
    
    void aniadir (const char* cadena);
    
    void leer(std::istream& flujo);
    
    void mostrar(std::ostream& flujo) const;
    
    void ordenar(int (*comparar)(const char*, const char*) );
    
    
private:
    void inicializar(int capacidad = 4);

private:
    char** _cadenas;     // Array dinámico de cadenas tipo C
    int _ncads;          // Número de cadenas actualmente en el array
    int _capacidad;      // Capacidad delarray dinámico;
    
    static const int NCARACTERES = 1000;   // Suponemos líneas con menos de 1000 char
};

#endif /* VECTORCADENAS_H */

