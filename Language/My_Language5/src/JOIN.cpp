/*
 * Metodología de la Programación: Language5
 * Curso 2022/2023
 */

/** 
 * @file JOIN.cpp
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
    outputStream << "JOIN [-t|-b] [-o <outputFile.bgr>] <file1.bgr> [<file2.bgr> ... <filen.bgr>] " << endl;
    outputStream << "       join the Language files <file1.bgr> <file2.bgr> ... into <outputFile.bgr>" << endl;
    outputStream << endl;
    outputStream << "Parameters:" << endl;
    outputStream << "-t|-b: text mode or binary mode for the output file (-t by default)" << endl;
    outputStream << "-o <outputFile.bgr>: name of the output file (output.bgr by default)" << endl;
    outputStream << "<file*.bgr>: each one of the files to be joined" << endl;
}

/**
 * This program reads an undefined number of Language objects from the files
 * passed as parameters to main(). It obtains as result the union of all the 
 * input Language objects. The result is then sorted by decreasing order of 
 * frequency and alphabetical order of bigrams when there is any tie in 
 * frequencies. Finally, the resulting Language is saved in an output file. The 
 * program must have at least an input file. 
 * Running example:
 * >  JOIN [-t|-b] [-o <outputFile.bgr>] <file1.bgr> [<file2.bgr> ... <filen.bgr>]
 * @param argc The number of command line parameters
 * @param argv The vector of command line parameters (cstrings)
 * @return 0 If there is no error; a value > 0 if error
 */
int main(int argc, char* argv[]) {
        
    // Default values
    char mode = 't';      // Flag for writing in binary mode.
    std::string output = "output.bgr";
    
    
    // Number of the parameter being checked
    int num_param = 1;
    
    
    bool opt_twice = false; // Flag. Checks if an option has been used twice
    bool not_enough_params = false; // Flag. Checks that there are enough parameters.
    bool incorrect_option = false; // Flag. Checks that no incorrect option has been given.
    
    // Flags for options already used;
    bool bt_opt = false;
    bool name_opt = false;
    
    // At least there is one file
    not_enough_params = argc <= num_param;
    
    // While all the flags are correct and the next parameter is an option...
    while (!opt_twice && !not_enough_params && !incorrect_option
             && argv[num_param][0] == '-'){
        
        // The next parameter must exist. At the end, it will be, at least, a file.
        not_enough_params = argc <= num_param+1;
        
        ///// Checks bt_opt /////
        if (    (strcmp(argv[num_param], "-b") == 0) ||
                (strcmp(argv[num_param], "-t") == 0)    ) {
            
            if (!bt_opt){ // Option yet not used
                bt_opt = true;
                mode = argv[num_param][1];
                num_param++;
            }
            else opt_twice = true;
        } // bt_opt checked
        
        
        ///// Checks name_opt /////
        else if (strcmp(argv[num_param], "-o") == 0) {
            
            if (!name_opt){ // Option yet not used
                
                not_enough_params = argc <= ++num_param;

                output = argv[num_param];
                num_param++;
            }
            else opt_twice = true;
        } // name_opt checked
        
        else
            incorrect_option = true;
        
        
    } // options checked.   while (argv[num_param][0] == '-' && !opt_twice && !not_enough_params)
    
    
    
    if (opt_twice || not_enough_params || incorrect_option){
        showEnglishHelp(cerr);
        return 1;
    }
    
    
    // num_param is the first .bgr to work on;
    Language lang, aux;
    lang.load(argv[num_param++]);
    
    for (int num_lang = num_param; num_lang < argc; num_lang++){
        
        // Qué hacer si tiene distinto idioma
        
        aux.load(argv[num_param]);
        lang += aux;
    }
    
    lang.sort();
    
    lang.save(output.c_str(), mode);
    
    
    return 0;
            
}

