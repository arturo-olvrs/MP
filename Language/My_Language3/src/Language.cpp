/** 
 * @file Language.cpp
 * @author Arturo Olivares Martos <2004.olivares@gmail.com>
 * @date 27 de Marzo de 2023, 17:49
 */


#include <fstream>
#include "Language.h"
#include "BigramFreq.h"

using namespace std;

const string Language::MAGIC_STRING_T="MP-LANGUAGE-T-1.0";

Language::Language():
    _languageId("unknown"),
    _size(0)
{}

Language::Language(const int numberBigrams){
    if (numberBigrams<0 || numberBigrams>DIM_VECTOR_BIGRAM_FREQ){
        
        string err = "Language::Language(int numberBigrams): \n";
        err += "Invalid number of bigrams: " + to_string(numberBigrams) + "\n";
        throw out_of_range(err);
    }
    
    _languageId = "unknown";
    _size = numberBigrams; 
}

const std::string& Language::getLanguageId() const{
    return _languageId;
}

void Language::setLanguageId(const std::string& id){
    _languageId = id;
}

const BigramFreq& Language::at(const int index) const{
    
    if (index<0 || index>=_size){
        string err;
        err += "const BigramFreq& Language::at(int index) const \n";
        err += "Invalid position " + to_string(index);
           
        throw out_of_range(err);
    }
    
    return _vectorBigramFreq[index];
}

BigramFreq& Language::at(int index){
    
    if (index<0 || index>=_size){
        string err;
        err += "BigramFreq& Language::at(int index) \n";
        err += "Invalid position " + to_string(index);
           
        throw out_of_range(err);
    }
    
    return _vectorBigramFreq[index];
}

int Language::getSize() const{
    return _size;
}

double Language::getDistance(const Language& otherLanguage) const{
    
    if (_size == 0){
        string err;
        err += "double Language::getDistance(const Language& otherLanguage) const \n";
        err += "The size of the implicit object is 0.";
           
        throw std::invalid_argument(err);
    }
    
    double dist = 0;
    
    
    for (int i=0; i<_size; i++){
        
        int rank_this = i; // = findBigram(_vectorBigramFreq[i]);
        
        int rank_other = otherLanguage.findBigram(_vectorBigramFreq[i].getBigram());
        if (rank_other == -1) // It is not found in otherLanguage
            rank_other = _size;
        
        dist += abs(rank_this - rank_other);
    }
    
    dist /= _size*_size;
    
    return dist;
}

int Language::findBigram(const Bigram& bigram) const{
    
    int index_searched = -1;
    
    int pos=0;
    while ((pos < _size) && (index_searched == -1))

        if (_vectorBigramFreq[pos].getBigram().toString() == bigram.toString())
            index_searched = pos;
    
        else pos++;
    
    return index_searched;
}


std::string Language::toString() const{
    
    string output;
    
    output += to_string(_size) + "\n";
    
    for (int i=0; i<_size; i++)
        output += _vectorBigramFreq[i].toString() + "\n";
    
    return(output);
}


void Language::sort(){
    
    // Insertion Algorithm
    
    for (int left = 1; left < _size; left++){
    
        BigramFreq to_insert = _vectorBigramFreq[left];
    
        int i = left;
        while (( i > 0 ) && !to_insert.isLower(_vectorBigramFreq[i-1]) ) {
            
            // Displaces to the right the lower values
            _vectorBigramFreq[i] = _vectorBigramFreq[i-1];
            
            i--;
        }
        
        _vectorBigramFreq[i] = to_insert;
    }
}

void Language::save(const char fileName[]) const{
    
    ofstream outputStream;
    
    outputStream.open(fileName);
    
    if (!outputStream){
        
        string fileName_str = fileName;
        string err;
        err += "void Language::save(const char fileName[]) const";
        err += "The file " + fileName_str + " couldn't be oppened";
        
        throw ios_base::failure(err);
    }
    
    outputStream << MAGIC_STRING_T << endl;
    outputStream << _languageId << endl;
    
    outputStream << toString();
    
    outputStream.close();
}


void Language::load(const char fileName[]){
    
    ifstream inputStream;
    
    inputStream.open(fileName);
    if(!inputStream){
        
        string fileName_str = fileName;
        
        string err;
        err += "void Language::load(const char fileName[]) const\n";
        err += "The file " + fileName_str + " couldn't be oppened";
        
        throw ios_base::failure(err);
    }
    
    
    // Reads the magic_string
    string tmp_magic_string;
    inputStream >> tmp_magic_string;
    
    if (tmp_magic_string != MAGIC_STRING_T){
        string err;
        err += "void Language::load(const char fileName[]) const\n";
        err += "The MAGIC_STRING_T expected was " + MAGIC_STRING_T + "\n";
        err += "The MAGIC_STRING_T recieved was " + tmp_magic_string + "\n";
        
        throw invalid_argument(err);
    }
    
    
    // Reads the language
    inputStream >> _languageId;
    
    
    // Reads the number of bigram_freq that are going to be given
    int num_bigramFreqs;
    inputStream >> num_bigramFreqs;
    
    if (num_bigramFreqs < 0 || num_bigramFreqs > DIM_VECTOR_BIGRAM_FREQ){
        string err;
        err += "void Language::load(const char fileName[]) const\n";
        err += "Invalid number of pairs of bigram and frequency: " + to_string(num_bigramFreqs)+"\n";
        
        throw out_of_range(err);
    }
    
    
    // Reads each bigram_freq
    BigramFreq BigramFreq_aux;
    Bigram Bigram_aux;
    _size = 0;
    
    for (int i=0; i <num_bigramFreqs; i++){
        
        // Reads the bigram
        inputStream >> Bigram_aux.at(0) >> Bigram_aux.at(1);
        
        // Reads the frequency
        int frequency_tmp;
        inputStream >> frequency_tmp;
        
        BigramFreq_aux.setFrequency(frequency_tmp);
        BigramFreq_aux.setBigram(Bigram_aux);
        
        
        // Adds the Bigram_Freq_aux
        _vectorBigramFreq[i] = BigramFreq_aux;
        _size ++;
    }
    
    
    // Closes the file
    inputStream.close();
    
}


void Language::append(const BigramFreq& bigramFreq){
    
    int index = findBigram(bigramFreq.getBigram());
    
    if (index == -1){ // Not found
        
        if (_size >= DIM_VECTOR_BIGRAM_FREQ){ // Array full. It does not fit
            
            string err;
            err += "void Language::append(const BigramFreq& bigramFreq)\n";
            err += "The array is full. It does not fit";
            
            throw out_of_range (err);
        }
        
        _vectorBigramFreq[_size] = bigramFreq;
        _size ++;
    }
    
    else { // Found
        
        int new_frequency = _vectorBigramFreq[index].getFrequency() + bigramFreq.getFrequency();
        _vectorBigramFreq[index].setFrequency(new_frequency);
    }
}


void Language::join(const Language& language){
    
    for (int i=0; i < language._size; i++)
        append(language._vectorBigramFreq[i]);
}