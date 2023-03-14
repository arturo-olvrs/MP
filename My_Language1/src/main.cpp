/** 
 * @file   main.cpp
 * 
 * @brief This program reads from the stardard input, an integer n (number of elements) 
 * and a list of n pairs bigram-frequency. The pairs are stored in an array, 
 * and then it is sorted in decreasing order of frequency. After that, 
 * all the bigrams are changed to uppercase. The sorted array is finally shown 
 * in the stardard output. 
 * Running example:
 * > language1 < data/miniquijotebigrams.txt 
 * 
 * @author arturoolvrs
 * 
 * @date 2 de marzo de 2023, 10:52
 */

#include <iostream>
#include <string>
#include "Bigram.h"
#include "BigramFreq.h"
#include "ArrayBigramFreqFunctions.h"

using namespace std;

int main(void) {
    
    // Dimension of the BigramFreq array
    const int DIM = 1000;
    
    BigramFreq array[DIM];
    int nElements=0;
    
    readArrayBigramFreq(array, DIM, nElements);
    sortArrayBigramFreq(array, nElements);
    toUpperArrayBigramFreq(array, nElements);
    
    printArrayBigramFreq(array, nElements);
    
    return 0;
}
