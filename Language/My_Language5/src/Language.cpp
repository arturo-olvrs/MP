/** 
 * @file Language.cpp
 * @author Arturo Olivares Martos <2004.olivares@gmail.com>
 * @date 28 de Mayo de 2023, 17:49
 */


#include <iostream>
#include <fstream>
#include <math.h>       /* fabs */
#include "Language.h"
#include "BigramFreq.h"

using namespace std;

const string Language::MAGIC_STRING_T="MP-LANGUAGE-T-1.0";
const string Language::MAGIC_STRING_B="MP-LANGUAGE-B-1.0";


Language::Language():
    _languageId("unknown")
{
    this->allocate(0);
}

Language::Language(const int numberBigrams){
    if (numberBigrams<0){
        
        string err = "Language::Language(int numberBigrams): \n";
        err += "Invalid number of bigrams: " + to_string(numberBigrams) + "\n";
        throw out_of_range(err);
    }
    
    _languageId = "unknown";
    allocate(numberBigrams);
}

Language::~Language(){
    
    deallocate();
}

Language::Language(const Language& orig){
    
    this->_languageId = orig._languageId;
    this->_size = orig._size;
    
    _vectorBigramFreq = new BigramFreq[_size];
    for(int i=0; i<_size; i++)
        this->_vectorBigramFreq[i] = orig._vectorBigramFreq[i];
}

Language& Language::operator=(const Language& orig){
    
    if (&orig != this){ // It is not the same object
        this->deallocate();
        
        this->_languageId = orig._languageId;
        this->_size = orig._size;

        _vectorBigramFreq = new BigramFreq[_size];
        for(int i=0; i<_size; i++)
            this->_vectorBigramFreq[i] = orig._vectorBigramFreq[i];
    }
    
    return *this;
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
        
        // cout << rank_this << " " << rank_other << endl;
        if (rank_other == -1) // It is not found in otherLanguage
            rank_other = _size;
        
        dist += fabs(rank_this - rank_other);
    }
    
    // std::cout << dist << std::endl;
    
    dist /= (_size*_size);
    
    // std::cout << dist << std::endl;
    
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
    
    output += this->getLanguageId() + "\n";
    output += to_string(this->getSize()) + "\n";
    
    for (int i=0; i<_size; i++)
        output += _vectorBigramFreq[i].toString() + "\n";
    
    return(output);
}


void Language::sort(){
    
    // Insertion Algorithm
    
    for (int left = 1; left < _size; left++){
    
        BigramFreq to_insert = _vectorBigramFreq[left];
    
        int i = left;
        while (( i > 0 ) && (to_insert >= _vectorBigramFreq[i-1]) ) {
            
            // Displaces to the right the lower values
            _vectorBigramFreq[i] = _vectorBigramFreq[i-1];
            
            i--;
        }
        
        _vectorBigramFreq[i] = to_insert;
    }
}

void Language::save(const char fileName[], char mode) const{
    
    if (mode == 'b'){
        
        ofstream outputStream;
    
        outputStream.open(fileName, ios::binary|ios::out);

        if (!outputStream){

            string fileName_str = fileName;
            string err;
            err += "void Language::save(const char fileName[]) const";
            err += "The file " + fileName_str + " couldn't be oppened";

            throw ios_base::failure(err);
        }

        outputStream << MAGIC_STRING_B << endl;
        outputStream << _languageId << endl;
        outputStream << _size << endl;
        
        for (int i=0; i<_size; i++)
            this->at(i).serialize(outputStream);

        outputStream.close();
        
    } // mode == b
    
    else if (mode == 't'){
        
        ofstream outputStream;
    
        outputStream.open(fileName, ios::out);

        if (!outputStream){

            string fileName_str = fileName;
            string err;
            err += "void Language::save(const char fileName[]) const";
            err += "The file " + fileName_str + " couldn't be oppened";

            throw ios_base::failure(err);
        }

        outputStream << MAGIC_STRING_T << endl;
        outputStream << *this << endl;

        outputStream.close();
    } // mode = t
       
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
    
    if (tmp_magic_string != MAGIC_STRING_T && tmp_magic_string != MAGIC_STRING_B){
        string err;
        err += "void Language::load(const char fileName[]) const\n";
        err += "Invalid magic string.\n";
        err += "The MAGIC_STRING recieved was " + tmp_magic_string + "\n";
        
        throw invalid_argument(err);
    }
    
    inputStream.close();
    
    if (tmp_magic_string == MAGIC_STRING_T){
        
        inputStream.open(fileName, ios::in);

        inputStream >> tmp_magic_string;
        inputStream.ignore();
        
        inputStream >> *this;

        inputStream.close();
        
    } // mode == t
    
    else if (tmp_magic_string == MAGIC_STRING_B){
        
        int nBigrams;
        
        inputStream.open(fileName, ios::in|ios::binary);

        inputStream >> tmp_magic_string;
        inputStream >> _languageId;
        inputStream >> nBigrams;
        inputStream.ignore(); // It jumps the last "\n"
        
        deallocate();
        allocate(nBigrams);
        
        for (int i=0; i<nBigrams; i++)
            this->at(i).deserialize(inputStream);
        
        inputStream.close();
        
    } // mode == t
    
}


void Language::append(const BigramFreq& bigramFreq){
    
    int index = findBigram(bigramFreq.getBigram());
    
    if (index == -1){ // Not found
        
        reallocate(_size+1); // It saves memory for a new object
        this->_vectorBigramFreq[_size - 1] = bigramFreq;
    }
    
    else { // Found
        
        int new_frequency = _vectorBigramFreq[index].getFrequency()
                                + bigramFreq.getFrequency();
        _vectorBigramFreq[index].setFrequency(new_frequency);
    }
}


const BigramFreq& Language::operator[](int index) const{
    
    return _vectorBigramFreq[index];
}


BigramFreq& Language::operator[](int index){
    
    return _vectorBigramFreq[index];
}


Language& Language::operator+=(const Language& language){
    
    for (int i=0; i < language._size; i++)
        append(language._vectorBigramFreq[i]);
    
    return *this;
}






/* //Método antiguo, sustituido por +=
 * 
void Language::join(const Language& language){
    
    for (int i=0; i < language._size; i++)
        append(language._vectorBigramFreq[i]);
}*/


void Language::allocate(int nElements){
    
    _size = 0;
    _vectorBigramFreq = nullptr;
            
    if (nElements > 0){
        
        _vectorBigramFreq = new BigramFreq[nElements];
        _size = nElements;
    }
}


void Language::deallocate(){
    
    if (_size > 0)
        delete[] _vectorBigramFreq;
        
    _vectorBigramFreq = nullptr;
    _size = 0;
}

void Language::reallocate(int newSize){
        
    if (newSize>0){
        
        int min_size = _size < newSize ? _size : newSize;
        
        BigramFreq* aux = new BigramFreq[newSize];
        for(int i=0; i<min_size; i++)
            aux[i] = this->_vectorBigramFreq[i];
            
        this->deallocate();
        this->_vectorBigramFreq = aux;
        _size = newSize;
        
        aux = nullptr;
        delete aux;
    }
}


std::ostream& operator<<(std::ostream& os, const Language& language){
    
    
    os << language.toString();
    
    return os;
}


std::istream& operator>>(std::istream& is, Language& language){
    
    // Clears the language
    language.deallocate();
    
    
    std::string langId_aux;
    // Reads the language
    is >> langId_aux;
    language.setLanguageId(langId_aux);
    
    
    // Reads the number of bigram_freq that are going to be given
    int num_bigramFreqs;
    is >> num_bigramFreqs;
    
    if (num_bigramFreqs < 0){
        string err;
        err += "std::istream& operator>>(std::istream& is, Language& language)\n";
        err += "Invalid number of pairs of bigram and frequency: " + to_string(num_bigramFreqs)+"\n";
        
        throw out_of_range(err);
    }
    
    language.allocate(num_bigramFreqs);
    
    
    // Reads each bigram_freq
    BigramFreq BigramFreq_aux;
    
    
    for (int i=0; i <num_bigramFreqs; i++){
        
        // Reads the bigram
        is >> BigramFreq_aux;
        
        // Adds the Bigram_Freq_aux
        language.at(i) = BigramFreq_aux;
    }
        
    return is;
}

