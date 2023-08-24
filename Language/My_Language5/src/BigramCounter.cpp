/*
 * Metodología de la Programación: Language5
 * Curso 2022/2023
 */

/** 
 * @file BigramCounter.cpp
 * @author Arturo Olivares Martos <2004.olivares@gmail.com>
 * @date 28 de Mayo de 2023, 17:49
 */

#include <cstring>
#include <fstream>
#include "BigramCounter.h"

/**
 * DEFAULT_VALID_CHARACTERS is a c-string that contains the set of characters
 * that will be considered as part of a word (valid chars). 
 * The characters not in the c-string will be considered as separator of words.
 * The constructor of the class BigramCounter uses this c-string as a 
 * default parameter. It is possible to use a different c-string if that
 * constructor is used with a different c-string
 */
const char* const BigramCounter::DEFAULT_VALID_CHARACTERS="abcdefghijklmnopqrstuvwxyz\xE0\xE1\xE2\xE3\xE4\xE5\xE6\xE7\xE8\xE9\xEA\xEB\xEC\xED\xEE\xEF\xF0\xF1\xF2\xF3\xF4\xF5\xF6\xF8\xF9\xFA\xFB\xFC\xFD\xFE\xFF";


BigramCounter::BigramCounter(const std::string& validChars){
    
    
    _validCharacters = validChars;
    
    
    int nChars = validChars.length();
    
    // Allocates memory for the matrix;
    allocate(nChars, nChars);
    
    // Sets to zero.
    this->clean();
}




BigramCounter::BigramCounter(const BigramCounter& orig){
    
    int nChars = orig.getSize();
    allocate(nChars, nChars);
    
    
    this->copy(orig);
}


BigramCounter::~BigramCounter(){
    
    deallocate();
}


int BigramCounter::getSize() const{
    
    return _validCharacters.length();
}


int BigramCounter::getNumberActiveBigrams() const{
    
    int nChars = this->getSize();
    
    int nActive = 0;
    
    for (int fil=0; fil<nChars; fil++)
        for (int col=0; col<nChars; col++)
            if ((*this)(fil,col) > 0)
                nActive ++;
    
    return nActive;
}



bool BigramCounter::setFrequency(const Bigram& bigram, int frequency){

    int index_1 = _validCharacters.find(bigram.at(0));
    int index_2 = _validCharacters.find(bigram.at(1));
    
    bool found = (index_1 != std::string::npos) &&
                 (index_2 != std::string::npos);
    
    if (found)
        (*this)(index_1, index_2) = frequency;
    
    return found;
}


void BigramCounter::increaseFrequency(const Bigram& bigram, int frequency){
    
    int index_1 = _validCharacters.find(bigram.at(0));
    int index_2 = _validCharacters.find(bigram.at(1));
    
    bool found = (index_1 != std::string::npos) &&
                 (index_2 != std::string::npos);
    
    if (!found){
        std::string err;
        err += "void BigramCounter::increaseFrequency(const Bigram& bigram, int frequency) \n";
        err += "Bigram " + bigram.getText() + " not found.\n";
           
        throw std::invalid_argument (err);
    }
    else{
        
        if ( frequency == 0 ) frequency = 1; // It always adds at least one
            
        (*this)(index_1, index_2) += frequency;
    }
}



BigramCounter& BigramCounter::operator=(const BigramCounter& orig){
    
    if (&orig != this){
        
        this-> deallocate();
        
        int nChars = orig.getSize();
        allocate(nChars, nChars);


        this->copy(orig);
    }
    
    
    return *this;
}



BigramCounter& BigramCounter::operator+=(const BigramCounter& rhs){
    
    
    if (this->_validCharacters == rhs._validCharacters){
        int nChars = rhs.getSize();
        
        
        // Both have the same matrix with different frequencies.
        for (int fil=0; fil<nChars; fil++)
            for (int col=0; col<nChars; col++)

                (*this)(fil, col) += rhs(fil, col);
            
    } // if (this->_validCharacters == rhs->_validCharacters)
            
    
    return *this;
}


void BigramCounter::calculateFrequencies(const char* fileName){
    
    
    // Opening the file
    std::ifstream inputStream;
    
    inputStream.open(fileName);
    if(!inputStream){
        
        std::string fileName_str = fileName;
        
        std::string err;
        err += "void BigramCounter::calculateFrequencies(const char*& fileName)\n";
        err += "The file " + fileName_str + " couldn't be oppened.";
        
        throw std::ios_base::failure(err);
    }
    
    // Cleans the matrix
    this->clean();
    
    
    // Reading the file
    std::string line;
    while(getline(inputStream, line)){
        
        // Converts to lowercase
        for (int i=0; i<line.length(); i++)
            line.at(i) = tolower(line.at(i));
        
        
        int init = 0;                       // First candidate to start the bigram
        int last_init = line.length()-1;    // Last candidate to start the bigram
        
        // It searches the first valid character
        while ((init < last_init) && !isValidCharacter(line.at(init), _validCharacters))
            init ++;
        
        
        while (init < last_init){

            char first = line.at(init);         // First character of the candidate to bigram
            char second = line.at(init+1);      // Second character of the candidate to bigram


            if (isValidCharacter(second, _validCharacters)){

                this->increaseFrequency(Bigram(first, second));
                init ++;
            }

            else {
                // If the second character is not valid, it "jumps" two positions
                //      and finds the next valid character
                init+=2;
                // It searches the next valid character
                while ((init < last_init) && !isValidCharacter(line.at(init), _validCharacters))
                    init ++;
            }

        } //while (init < last_init)
    } // while getline
    
    
    
    // Closes the file
    inputStream.close();
    
}






Language BigramCounter::toLanguage() const{
    
    const int nACTIVE = this->getNumberActiveBigrams();
    Language lang(nACTIVE);
    
    
    const int nCHARS = this->getSize();
    BigramFreq bigramFreq_aux;
    Bigram bigram_aux;
    
    int n_added = 0;
    bool finished = false; // Flag to stop searching when finished
    
    for (int fil=0; fil<nCHARS & !finished; fil++){
        bigram_aux.at(0) = this->_validCharacters.at(fil);
        
        for (int col=0; col<nCHARS & !finished; col++){
            
            bigramFreq_aux.setFrequency((*this)(fil, col));
            
            // Only is the frequency is positive is added
            if (bigramFreq_aux.getFrequency()>0){
                
                bigram_aux.at(1) = this->_validCharacters.at(col);
                bigramFreq_aux.setBigram(bigram_aux);
            
                lang.at(n_added) = bigramFreq_aux;
                
                n_added ++; // It is registered as added
                finished = n_added >= nACTIVE; // finished if all have been added
       
            } // if active
        } // for col
    } // for fil
    
    
    lang.sort();
    
    
    return lang;
}



void BigramCounter::allocate(int nrows, int ncols){
    
    _frequency = nullptr;
    
    if (nrows > 0 && ncols >0){
    
        _frequency = new int* [nrows];

        for (int row=0; row<nrows; row++)    
            _frequency[row] = new int [ncols];
    }
}


void BigramCounter::deallocate(){
        
    if (_frequency != nullptr){
        for (int row=0; row < this->getSize(); row++)    
            delete [] _frequency[row];
        
        delete [] _frequency;

        _frequency = nullptr;
    }
}


void BigramCounter::copy(const BigramCounter& orig){
    
    if (&orig != this){
        
        this->_validCharacters = orig._validCharacters;
        
        int nChars = orig.getSize();

        // Copies the orig in *this.
        for (int fil=0; fil<nChars; fil++)
            for (int col=0; col<nChars; col++)
                (*this)(fil,col) = orig(fil, col);
    }
}


void BigramCounter::clean(){
        
    int nChars = this->getSize();
    
    // Sets to zero.
    for (int fil=0; fil<nChars; fil++)
        for (int col=0; col<nChars; col++)
            (*this)(fil,col)=0;
}



const int& BigramCounter::operator()(int row, int column) const{
    
    return _frequency[row][column];
}


int& BigramCounter::operator()(int row, int column){
    
    return _frequency[row][column];
}