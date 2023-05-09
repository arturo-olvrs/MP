/** 
 * @file main.cpp
 * @author Arturo Olivares Martos <2004.olivares@gmail.com>
 * @date 26 de Abril de 2023, 17:49
 * 
 * @brief This program reads an undefined number of Language objects from the set of 
 * files passed as parameters to main(). All the Languages object, except the 
 * first one, must be stored in a dynamic array of Language objects. Then, 
 * for each Language in the dynamic array, this program prints to the 
 * standard output the name of the file of that Language and the distance from 
 * the first Language to the current Language. 
 * Finally, the program should print in the standard output, the name of 
 * the file with the Language with the minimum|maximum distance to the Language 
 * of the first file and its language identifier.
 * 
 * At least, two Language files are required to run this program.
 * Running example:
 * > language3 [-t min|max] <file1.bgr> <file2.bgr> [  ... <filen.bgr>] 
 */

#include <iostream>
#include <cstring>

#include "Language.h"

using namespace std;

/**
 * Shows help about the use of this program in the given output stream
 * @param outputStream The output stream where the help will be shown (for example,
 * cout, cerr, etc) 
 */
void showEnglishHelp(ostream& outputStream) {
    outputStream << "Error, run with the following parameters:" << endl;
    outputStream << "language3 [-t min|max] <file1.bgr> <file2.bgr> [ ... <filen.bgr>]" << endl;
}


int main(int argc, char* argv[]) {
    
    // Checks that the program is called with at least is called with 3 params.
    if (argc < 3){
        showEnglishHelp(std::cerr);
        return 1;
    }
    
    bool min = true; // Default option
    
    int first_arg = 1; // First language to load
    
    
    
    // Checks if an option has been provided
    if (argv[1][0] == '-'){
        
        // Checks if THE correct option has been provided
        if (strcmp(argv[1], "-t") == 0){

            first_arg = 3;

            if ( (argc - first_arg) < 2 ){

                // Not enough languages
                showEnglishHelp(std::cerr);
                return 1;
            }


            if (strcmp(argv[2], "max") == 0){
                min = false;
            }

            else if (strcmp(argv[2], "min") != 0){
                // -t has been provided but not followed by min|max

                showEnglishHelp(std::cerr);
                return 1;
            }
        } //(strcmp(argv[1], "-t") == 0)
        
        else{
            // An option has been provided but it is not "-t
            
            showEnglishHelp(std::cerr);
            return 1;
        }
    
    } // if (argv[1][0] == "-"){
    
    
    
    
    // Loads the reference language
    Language reference_language;
    reference_language.load(argv[first_arg]);
    
    
    int num_languages = argc - first_arg -1; //-1 because the first language is not stored.
    
    // Reserves dynamic memory and loads each language
    Language *languages = nullptr;
    languages = new Language [num_languages];
    
    for (int i=0; i<num_languages; i++)
        languages[i].load(argv[first_arg + i + 1]);
    
    
    // Searched the min_max language and prints each distance
    double min_max_dist = min ? 1 : 0; // distance \in [0,1]
    int min_max_index = -1;
    
    for(int i=0; i<num_languages; i++){
        
        double dist = reference_language.getDistance(languages[i]);
        
        // If the min is searched, a new min has been found if dist <= min_dist.
        // Else, (max is searched), a new max has been found if dist >= max_dist.
        bool new_min_max = min ? dist <= min_max_dist : dist >= min_max_dist;
        
        if (new_min_max){
            min_max_index = i;
            min_max_dist = dist;
        }
        
        // the distance to each language is printed
        cout << "Distance to " << argv[i+first_arg + 1] << ": " << dist << endl;
        
    } // for languages
    
    
    // Prints the min_max language. 
    if (min){
        cout << "Nearest language file: " << argv[min_max_index+first_arg + 1] << endl;
        cout << "Identifier of the nearest language: " << languages[min_max_index].getLanguageId() << endl;
    }
    else{
        cout << "Farthest language file: " << argv[min_max_index+first_arg + 1] << endl;
        cout << "Identifier of the farthest language: " << languages[min_max_index].getLanguageId() << endl;
    }

    
    // Deletes dynamic array
    delete[] languages; 


    return 0;
        
}