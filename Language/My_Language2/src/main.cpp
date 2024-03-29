/** 
 * @file main.cpp
 * @author Arturo Olivares Martos <2004.olivares@gmail.com>
 * @date 27 de Marzo de 2023, 17:49
 * 
 * @brief This program reads an undefined number of Language objects from the files
 * passed as parameters to main(). It obtains as result the union of all the 
 * input Language objects. The result is then sorted by decreasing order of 
 * frequency and alphabetical order of bigrams when there is any tie in 
 * frequencies. Finally the resulting Language is saved in an output file. The 
 * program must have at least an input file and an output file. 
 * The output Language will have as language identifier, the one of the first
 * file (<file1.bgr>). If an input file <file*.bgr> has a language identifier
 * different from the one of the first file (<file1.bgr>), then it will not
 * be included in the union.
 * Running example:
 * > language2 <file1.bgr> [<file2.bgr> ... <filen.bgr>] <outputFile.bgr> 
 */

#include <iostream>
#include "Language.h"

using namespace std;

/**
 * Shows help about the use of this program in the given output stream
 * @param outputStream The output stream where the help will be shown (for example,
 * cout, cerr, etc) 
 */
void showEnglishHelp(ostream& outputStream) {
    outputStream << "Error, run with the following parameters:" << endl;
    outputStream << "language2 <file1.bgr> [<file2.bgr> ... <filen.bgr>] <outputFile.bgr> " << endl;
}

int main(int argc, char* argv[]) {
    
    // The program needs at least 3 parameters
    if (argc < 3){
        showEnglishHelp(cerr);
        return 1;
    }
    
    
    Language language_read;     // The language readed in each file
    Language language_joined;   // The laguage generated that is going to be saved.
    
    language_joined.load(argv[1]);  // The first language is loaded to set the language.
    
    
    for (int i=2; i < argc-1; i++){
        
        language_read.load(argv[i]);
        
        if(language_read.getLanguageId() == language_joined.getLanguageId())
            language_joined.join(language_read);
        
    }  
    
    language_joined.sort();
    language_joined.save(argv[argc-1]);
    
    return 0;
}

