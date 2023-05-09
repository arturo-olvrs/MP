/** 
 * @file   Bigram.cpp
 * @author arturoolvrs
 * 
 * @date 2 de marzo de 2023, 10:52
 */

#include <iostream>
#include "Bigram.h"


using namespace std;

Bigram::Bigram(const string& text){
    
    if (text.length() == 2)
        _text = text;
    
    else
        _text = "__";
}


Bigram::Bigram(char first, char second){
    _text += first;
    _text += second;
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
        err += "const char& Bigram::at(int index) const";
        err += "\n";
        err += "Invalid position " + to_string(index);
           
        throw std::out_of_range (err);
    }
    
    return _text.at(index);
}

char& Bigram::at(int index){
    if (index!=0 && index!=1){
        string err;
        err += "char& Bigram::at(int index)";
        err += "\n";
        err += "Invalid position " + to_string(index);
           
        throw std::out_of_range (err);
    }
    
    return _text.at(index);
}

bool isValidCharacter(char character, const std::string& validCharacters){
    
    return validCharacters.find(character) != std::string::npos;
}


void toUpper(Bigram &bigram){
    
    for (int i=0; i<2; i++)
        bigram.at(i) = toupper(bigram.at(i));
    
}