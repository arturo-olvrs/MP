/*
 * Metodología de la Programación: Language5
 * Curso 2022/2023
 */

/** 
 * @file CLASSIFY.cpp
 * @author Arturo Olivares Martos <2004.olivares@gmail.com>
 * @date 28 de Marzo de 2023, 17:49
 */


#include <cstring>
#include "BigramCounter.h"

using namespace std;



/**
 * Shows help about the use of this program in the given output stream
 * @param outputStream The output stream where the help will be shown (for example,
 * cout, cerr, etc) 
 */
void showEnglishHelp(ostream& outputStream) {
    outputStream << "Error, run with the following parameters:" << endl;
    outputStream << "CLASSIFY <text.txt> <lang1.bgr> [<lang2.bgr> <lang3.bgr> ....]" << endl;
    outputStream << "          Obtains the identifier of the closest language to the input text file" << endl;
    outputStream << endl;
}

/**
 * This program print the language identifier of the closest language 
 * for an input text file (<text.txt>) among the set of provided models:
 * <lang1.bgr>, <lang2.bgr>, ...
 * 
 * Running example:
 * > CLASSIFY  <text.txt> <lang1.bgr> [<lang2.bgr> <lang3.bgr> ...]
 * @param argc The number of command line parameters
 * @param argv The vector of command line parameters (cstrings)
 * @return 0 If there is no error; a value > 0 if error
 */
int main(int argc, char *argv[]) {
    
    
    if (argc <=2){ // Not enough parameters
        showEnglishHelp(cerr);
        return 1;
    }
    
    
    int num_file = 1;
        
    BigramCounter builder;
    
    builder.calculateFrequencies(argv[num_file++]);
    
    Language to_classify = builder.toLanguage();
    // std::cout << to_classify << std::endl;
   
    
    // Impossible values to search for the min
    int num_lang_detected = -1;
    double min_distance = 9999; //
    std::string lang_detected = "unknown";
    
    Language aux;
    
    // Iterate over each file
    for (num_file; num_file < argc; num_file++){
        
        
        aux.load(argv[num_file]);
        // std::cout << aux << std::endl;
        
        double distance = to_classify.getDistance(aux);        
        
        // If found a new min, it is updated
        if (distance < min_distance){
            
            min_distance = distance;
            num_lang_detected = num_file;
            lang_detected = aux.getLanguageId();
           
        }
    } // for file
    
    
    // Prints the final decision
    cout << "Final decision: "
         << "language " << lang_detected
         << " with a distance of " << min_distance << endl;
    
    
    return 0;
}

