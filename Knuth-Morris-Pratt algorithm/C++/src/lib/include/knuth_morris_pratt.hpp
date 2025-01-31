#ifndef KNUTH_MORRIS_PRATT_LIB_HPP
#define KNUTH_MORRIS_PRATT_LIB_HPP

#include <string>

/**
 * @brief Search for a pattern in a text using the Knuth-Morris-Pratt algorithm.
 * @param text The text to search in.
 * @param pattern The pattern to search for.
 * @return The index of the first occurrence of the pattern in the text or -1 if the pattern is not found. Also returns -1 in any of the corner cases (like empty pattern or text, pattern longer than text, etc.).
 */
int searchKnuthMorrisPratt(const std::string& text, const std::string& pattern);

#endif // KNUTH_MORRIS_PRATT_LIB_HPP
