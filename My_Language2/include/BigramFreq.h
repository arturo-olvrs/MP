/* 
 * @file   BigramFreq.h
 * @author Arturo Olivares Martos <2004.olivares@gmail.com>
 *
 * @date 13 de marzo de 2023, 18:12
 */

#ifndef BIGRAM_FREQ_H
#define BIGRAM_FREQ_H

#include <string>

#include "Bigram.h"

/**
 * @class BigramFreq
 * @brief A pair of a Bigram object and a frequency (an int), that gives the 
 * frequency of a Bigram (times it appears) in a text.
 */
class BigramFreq {
public:
    /**
     * @brief Base constructor. It builds a BigramFreq object with "__" as 
     * the text of the bigram and 0 as the frequency
     */
    BigramFreq();

    /**
     * @brief Gets a const reference to the Bigram of this BigramFreq object.
     * Query method
     * @return A const reference to the Bigram of this BigramFreq object
     */
    const Bigram& getBigram() const;

    /**
     * @brief Gets the frequency of this BigramFreq object
     * Query method
     * @return The frequency of this BigramFreq object
     */
    int getFrequency() const;

    /**
     * @brief Sets the Bigram of this BigramFreq object
     * Modifier method
     * @param bigram The new Bigram value for this object. Input parameter
     */
    void setBigram(const Bigram& bigram);

    /**
     * @brief Sets the frequency of this BigramFreq object. Modifier method.
     * @throw std::out_of_range if @p frequency is negative
     * @param frequency the new frequency value for this BigramFreq object. 
     * Input parameter
     */
    void setFrequency(const int frequency);
    
    /**
     * @brief Checks if the implicit bigram is lower than the explicit bigram.
     * It is lower if its frequency is lower and, if both frequencies are equal,
     * it is ordered alphabetically.
     * 
     * @param other explicit BigramFreq object.
     * 
     * @return @true if *this is lower than @p other
     *         @false if *this is greater than @p other 
     */
    bool isLower(const BigramFreq& other) const;
    
    /**
     * @brief Obtains a string with the string and frequency of the bigram
     * in this object (separated by a whitespace). Query method
     * @return A string with the string and frecuency of the bigram
     * in this object. 
     */
    std::string toString() const;

private:
    Bigram _bigram; ///< the Bigram object
    int _frequency; ///< the frequency
};


#endif /* BIGRAM_FREQ_H */

