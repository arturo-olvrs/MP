/** 
 * @file:   BiframFreq.cpp
 * @author: arturoolvrs
 * 
 * @date 13 de marzo de 2023, 18:10
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

bool BigramFreq::isLower(const BigramFreq& other) const{
    
    bool is_lower;
    
    if (_frequency != other._frequency)
        is_lower = _frequency < other._frequency;
    
    else // (_frequency == other._frequency)
        is_lower = _bigram.getText() > other._bigram.getText();
    
    
    return is_lower;
}

std::string BigramFreq::toString() const{
    return (_bigram.toString() + " " + std::to_string(_frequency));
}


