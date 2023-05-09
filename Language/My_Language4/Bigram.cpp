/** 
 * @file   Bigram.cpp
 * @author Arturo Olivares Martos <2004.olivares@gmail.com>
 * 
 * @date 2 de marzo de 2023, 10:52
 */

#include <iostream>
#include <cstring>
#include "Bigram.h"


using namespace std;

Bigram::Bigram(const string& text){
    
    if (text.length() == 2)
        strcpy(_text, text.c_str());
    
    else
        strcpy(_text, "__");
}


Bigram::Bigram(char first, char second){
    _text[0] = first;
    _text[1] = second;
    _text[2] = '\0';
}

Bigram::Bigram(const char text[]){
    if (strlen(text) == 2)
        strcpy(_text, text);
    else
        strcpy(_text, "__");
}

string Bigram::getText() const{
    return _text;
}


string Bigram::toString() const{
    return _text;
}


const char& Bigram::at(int index) const{
    if (index!=0 && index!=1){
        string err;
        err += "const char& Bigram::at(int index) const \n";
        err += "Invalid position " + to_string(index);
           
        throw std::out_of_range (err);
    }
    
    return _text[index];
}

char& Bigram::at(int index){
    if (index!=0 && index!=1){
        string err;
        err += "char& Bigram::at(int index)";
        err += "\n";
        err += "Invalid position " + to_string(index);
           
        throw std::out_of_range (err);
    }
    
    return _text[index];
}

void Bigram::toUpper(){
    for (int i=0; i<2; i++)
        _text[i] = toupper(_text[i]);
}

bool isValidCharacter(char character, const std::string& validCharacters){
    
    return validCharacters.find(character) != std::string::npos;
}