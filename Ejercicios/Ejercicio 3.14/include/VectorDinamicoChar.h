/* 
 * @file:   VectorDinamicoChar.h
 * @author: Arturo Olivares Martos <2004.olivares@gmail.com>
 *
 * @date 2 de Mayo de 2023, 1:20 PM
 */

#ifndef VECTORDINAMICOCHAR_H
#define VECTORDINAMICOCHAR_H

#include <fstream> // ifstream

class VectorDinamicoChar {
public:
    
    VectorDinamicoChar();
    VectorDinamicoChar(int capacidad);
   
    void liberar();
    
    void clear();
    
    void mostrar (std::ostream& flujo) const;
    
    void redimensionar ();
    
    void aniadir (char caracter);
    
    void leer(std::istream& flujo);
    
private:
    void inicializar(int capacidad = 10);
    

private:
    char* _arrayChar;    // array dinámico de char
    int _nCaracteres;    // nº de caracteres actualmente en el array
    int _capacidad;      // capacidad del array

};

#endif /* VECTORDINAMICOCHAR_H */

