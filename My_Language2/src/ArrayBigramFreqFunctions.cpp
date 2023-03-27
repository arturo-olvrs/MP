/* 
 * @file:   ArrayBigramFreqFunctions.cpp
 * @author: Arturo Olivares Martos <2004.olivares@gmail.com>
 * 
 * @date 13 de marzo de 2023, 18:13
 */

#include "ArrayBigramFreqFunctions.h"


void readArrayBigramFreq(BigramFreq array[], int dim, int &nElements){
    
    std::cin >> nElements;
    
    if (nElements > dim){
        
        std::cerr << nElements << " do not fit in the array. "
                  << dim << " elements read.";
        
        nElements = dim;
    }
    else if (nElements < 0){
        
        std::cerr << nElements << " negative. "
                  << "0" << " elements read.";
        
        nElements = 0;
    }
    
    char first, second;
    int frequency;
    
    for (int i=0; i<nElements; i++){
        
        std::cin >> first >> second >> frequency;
        
        tolower(first);
        tolower(second);
        
        array[i].setBigram(Bigram(first, second));
        array[i].setFrequency(frequency);
        
    }
    
    
}


void printArrayBigramFreq(const BigramFreq array[], int nElements){
    
    std::cout << nElements << std::endl;
    
    for (int i=0; i<nElements; i++){
        std::cout << array[i].toString() << std::endl;
    }
}

void swapElementsArrayBigramFreq(BigramFreq array[], int nElements, int first,
                int second){
    
    bool first_valid  = (0 <= first)  && (first  < nElements);
    bool second_valid = (0 <= second) && (second < nElements);
    
    if (!(first_valid && second_valid)){
        std::string err;
        err += "void swapElementsArrayBigramFreq(BigramFreq array[], ";
        err += "int nElements, int first, int second)";
        err += "\n";
        err += "Invalid position ";
        
        err += !first_valid ? std::to_string(first) : std::to_string(second);
        
           
        throw std::out_of_range (err);
    }
    
    // Swap elements
    BigramFreq aux = array[first];
    array[first] = array[second];
    array[second] = array[first];
}

void sortArrayBigramFreq(BigramFreq array[], int nElements){
    
    // Insertion Algorithm
    
    for (int left = 1; left < nElements; left++){
    
        BigramFreq to_insert = array[left];
    
        int i = left;
        while (( i > 0 ) && !to_insert.isLower(array[i-1]) ) {
            
            // Displaces to the right the lower values
            array[i] = array[i-1];
            
            i--;
        }
        
        array[i] = to_insert;
    }
}


void toUpperArrayBigramFreq(BigramFreq array[], int nElements){
    
    for(int i=0; i<nElements; i++){
 
        Bigram bigram = array[i].getBigram();
        bigram.toUpper();
        
        array[i].setBigram(bigram);
    }
}
