/** 
 * @file:   BiframFreq.cpp
 * @author: Arturo Olivares Martos <2004.olivares@gmail.com>
 * 
 * @date 28 de mayo de 2023, 18:10
 */

#include <cstring>
#include "BigramFreq.h"


BigramFreq::BigramFreq():
    _frequency(0), _bigram("__") {}

const Bigram& BigramFreq::getBigram() const{
    return _bigram;
}

int BigramFreq::getFrequency() const{
    
    return _frequency;
}

void BigramFreq::setBigram(const Bigram& bigram){
    _bigram = bigram;
}

void BigramFreq::setFrequency(int frequency){
    if (frequency < 0){
        
        std::string err;
        err += "void BigramFreq::setFrequency(int frequency)";
        err += "\n";
        err += "Invalid frequency " + std::to_string(frequency) + 
                ". It must be positive or zero.";
        
        throw std::out_of_range(err);
    }
    _frequency = frequency;
}


std::string BigramFreq::toString() const{
    return (_bigram.toString() + " " + std::to_string(_frequency));
}




void BigramFreq::serialize(std::ostream& outputStream) const{
    
    this->getBigram().serialize(outputStream);
    
    outputStream.write(reinterpret_cast<const char*>(&_frequency), sizeof(int));
}

void BigramFreq::deserialize(std::istream& inputStream){
    
    Bigram aux;
    aux.deserialize(inputStream);
    
    this->setBigram(aux);
    
    inputStream.read(reinterpret_cast<char*>(&_frequency), sizeof(int));
}


std::ostream& operator<<(std::ostream& os, const BigramFreq& bigramFreq){
    
    os << bigramFreq.toString();
    
    return os;
}


std::istream& operator>>(std::istream& is, BigramFreq& bigramFreq){
    
    Bigram bgr_aux;
    int freq_aux;
    
    is >> bgr_aux >> freq_aux;
    
    bigramFreq.setBigram(bgr_aux);
    bigramFreq.setFrequency(freq_aux);
    
    return is;
}


bool operator>(const BigramFreq& bigramFreq1, const BigramFreq& bigramFreq2){
    
    bool is_greater;
    
    if (bigramFreq1.getFrequency() != bigramFreq2.getFrequency())
        is_greater = bigramFreq1.getFrequency() > bigramFreq2.getFrequency();
    
    else // (frequency_1 == frequency_2)
        is_greater = bigramFreq1.getBigram().getText() < bigramFreq2.getBigram().getText() ;
    
    
    return is_greater;    
}


bool operator<(const BigramFreq& bigramFreq1, const BigramFreq& bigramFreq2){
    
    return bigramFreq2>bigramFreq1;   
}


bool operator==(const BigramFreq& bigramFreq1, const BigramFreq& bigramFreq2){
    
    return !(bigramFreq1>bigramFreq2 || bigramFreq1<bigramFreq2);
}


bool operator!=(const BigramFreq& bigramFreq1, const BigramFreq& bigramFreq2){
    
    return !(bigramFreq1 == bigramFreq2);
}

bool operator<=(const BigramFreq& bigramFreq1, const BigramFreq& bigramFreq2){
    
    return !(bigramFreq1 > bigramFreq2);
}

bool operator>=(const BigramFreq& bigramFreq1, const BigramFreq& bigramFreq2){
    
    return !(bigramFreq1 < bigramFreq2);
}




