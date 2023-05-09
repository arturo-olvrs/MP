/** 
 * @file   main.cpp
 * 
 * This program reads a text (without spaces) with a undefined number of 
 * characters and a text with two characters (bigram). It finds the bigrams 
 * contained in the first text, storing them in an array of Bigram. 
 * After that, the bigrams of the array are shown in the standard output. 
 * Then it converts to uppercase the bigrams in the array that are equals to the 
 * bigram of the second text. Finally the bigrams of the array are shown again 
 * in the standard output.
 * 
 * @author arturoolvrs
 * 
 * @date 2 de marzo de 2023, 10:52
 */

#include <iostream>
#include <string>
#include "Bigram.h"

using namespace std;

/**
 * 
 * @brief It converts a string to lowercase
 * @param cad string to convert to lowercase
 */
void toLower(string &cad){
    
    for (int i=0; i<cad.length(); i++)
        cad.at(i)=tolower(cad.at(i));
}


int main(void) {
    
    // This string contains the list of characters that are considered as
    // valid within a word. The rest of characters are considered as
    // separators
    const string validCharacters = "abcdefghijklmnopqrstuvwxyz\xE0\xE1\xE2\xE3\xE4\xE5\xE6\xE7\xE8\xE9\xEA\xEB\xEC\xED\xEE\xEF\xF0\xF1\xF2\xF3\xF4\xF5\xF6\xF8\xF9\xFA\xFB\xFC\xFD\xFE\xFF";
    
    
    // Read a text
    string text;
    cin >> text;
    toLower(text);
    
    // Read a bigram (text with two characters)
    string bigram_to_search;
    cin >> bigram_to_search;
    toLower(bigram_to_search);
    
    
    // Find the bigrams in text and put them in an array of Bigrams
    const int MAX_BIGRAMS = 50;
    /**
     * 
     * @var v_bigrams array that contains every bigram in the text.
     */
    Bigram v_bigrams[MAX_BIGRAMS];
    
    int num_bigrams = 0;    // Number of bigrams added
    
    /**
     * 
     * @brief It iterates over the supposedly initial character of the bigram.
     * If both the init and the next characters are valid, it is added as a bigram.
     *   
     */
    int init = 0;                       // First candidate to start the bigram
    int last_init = text.length()-1;    // Last canidate to start the bigram
    
    // It searches the first valid character
    while ((init < last_init) && !isValidCharacter(text.at(init), validCharacters))
        init ++;
    
    
    while ((init < last_init)  &&  (num_bigrams < MAX_BIGRAMS)){
        
        
        char first = text.at(init);         // First character of the candidate to bigram
        char second = text.at(init+1);      // Second character of the candidate to bigram

        
        if (isValidCharacter(second, validCharacters)){
            v_bigrams[num_bigrams]=Bigram(first, second);
            num_bigrams++;
            init ++;
        }
        else {
            // If the second character is not valid, it "jumps" two positions
            //      and finds the next valid character
            init+=2;
            // It searches the next valid character
            while ((init < last_init) && !isValidCharacter(text.at(init), validCharacters))
                init ++;
        }
        
    } //while ((init < last_init)  &&  (num_bigrams < MAX_BIGRAMS))
    
    
    // Show the bigrams stored in the array
    cout << num_bigrams << endl;
    for (int i=0; i<num_bigrams; i++)
        cout << v_bigrams[i].toString() << endl;
    
    // Convert to uppercase the bigrams in the array that are equals to input bigram
    for (int i=0; i<num_bigrams; i++)
        
        if (bigram_to_search == v_bigrams[i].toString())
            toUpper(v_bigrams[i]);
    
    
    cout << endl;
    
    // Show again the bigrams stored in the array
    cout << num_bigrams << endl;
    for (int i=0; i<num_bigrams; i++)
        cout << v_bigrams[i].toString() << endl;
    
    cout << endl;
    return 0;
}
