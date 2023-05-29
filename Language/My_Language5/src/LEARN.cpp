/*
 * Metodología de la Programación: Language5
 * Curso 2022/2023
 */

/** 
 * @file LEARN.cpp
 * @author Arturo Olivares Martos <2004.olivares@gmail.com>
 * @date 28 de Marzo de 2023, 17:49
 */

#include<cstring>
#include "BigramCounter.h"
using namespace std;

/**
 * Shows help about the use of this program in the given output stream
 * @param outputStream The output stream where the help will be shown (for example,
 * cout, cerr, etc) 
 */
void showEnglishHelp(ostream& outputStream) {
    outputStream << "Error, run with the following parameters:" << endl;
    outputStream << "LEARN [-t|-b] [-l languageId] [-o outputFilename] <text1.txt> [<text2.txt> <text3.txt> .... ]" << endl;
    outputStream << "           learn the model for the language languageId from the text files <text1.txt> <text2.txt> <text3.txt> ..." << endl;
    outputStream << endl;
    outputStream << "Parameters:" << endl;
    outputStream << "-t|-b: text mode or binary mode for the output file (-t by default)" << endl;
    outputStream << "-l languageId: language identifier (unknown by default)" << endl;
    outputStream << "-o outputFilename: name of the output file (output.bgr by default)" << endl;
    outputStream << "<text1.txt> <text2.txt> <text3.txt> ....: names of the input files (at least one is mandatory)" << endl;
}

/**
 * This program learns a Language model from a set of input tex files (tex1.txt,
 * tex2.txt, ...
 * Running example:
 * > LEARN [-t|-b] [-l languageId] [-o outputFilename] <text1.txt> [<text2.txt> <text3.txt> ....]
 * @param argc The number of command line parameters
 * @param argv The vector of command line parameters (cstrings)
 * @return 0 If there is no error; a value > 0 if error
 */

int main(int argc, char *argv[]) {  
    
    
    // Default values
    char mode = 't';      // Flag for writing in binary mode.
    std::string language = "unknown";
    std::string output = "output.bgr";
    
    
    // Number of the parameter being checked
    int num_param = 1;
    
    
    bool opt_twice = false; // Flag. Checks if an option has been used twice
    bool not_enough_params = false; // Flag. Checks that there are enough parameters.
    
    // Flags for options already used;
    bool bt_opt = false;
    bool name_opt = false;
    bool language_opt = false;
    
    while (argv[num_param][0] == '-' && !opt_twice && !not_enough_params){
        
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
        
        
        ///// Checks laguage_opt /////
        else if (strcmp(argv[num_param], "-l") == 0) {
            
            if (!language_opt){ // Option yet not used
                
                not_enough_params = argc <= ++num_param;

                language = argv[num_param];
                num_param++;
            }
            else opt_twice = true;
        } // laguage_opt checked
        
        
    } // options checked.   while (argv[num_param][0] == '-' && !opt_twice && !not_enough_params)
    
    
    
    if (opt_twice || not_enough_params){
        showEnglishHelp(cerr);
        return 1;
    }
    
    
    // num_param is the first .bgr to work on;
    
    
    BigramCounter builder;
    
    Language lang;
    lang.setLanguageId(language);
    
    for (int num_file = num_param; num_file < argc; num_file++){
        
        builder.calculateFrequencies(argv[num_file]);
        lang += builder.toLanguage();
    }
    
    lang.save(output.c_str(), mode);
    
    
    return 0;

}

