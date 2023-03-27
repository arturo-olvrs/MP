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

void Language::setLanguageId(const std::string id){
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

void Language::load(const char fileName[]){
    
    ifstream inputStream;
    
    inputStream.open(fileName);
    if(!inputStream){
        
        string err;
        err += "void Language::load(const char fileName[]) const\n";
        err += "The file couldn't be oppened";
        
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
    
    for (int i=0; i <num_bigramFreqs; i++){
        
        // Reads the bigram
        inputStream >> Bigram_aux.at(0) >> Bigram_aux.at(1);
        
        // Reads the frequency
        int frequency_tmp;
        inputStream >> frequency_tmp;
        
        BigramFreq_aux.setFrequency(frequency_tmp);
        BigramFreq_aux.setBigram(Bigram_aux);
        
        
        // Adds the Bigram_Freq_aux
        //append(BigramFreq_aux);
    }
    
    
    // Closes the file
    inputStream.close();
    
}


int Language::findBigram(const Bigram& bigram) const{
    
    return 0;
    
}


std::string Language::toString() const{
    
    return "Hola";
}

void Language::save(const char fileName[]) const{
    
    ofstream outputStream;
    
    outputStream.open(fileName);
    
    if (!outputStream){
        string err;
        err += "void Language::save(const char fileName[]) const";
        err += "The file couldn't be oppened";
        
        throw ios_base::failure(err);
    }
    
    
}
