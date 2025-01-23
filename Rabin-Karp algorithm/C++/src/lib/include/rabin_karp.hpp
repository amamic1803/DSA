#ifndef RABIN_KARP_LIB_HPP
#define RABIN_KARP_LIB_HPP

#include <string>

/**
 * @brief Search for a pattern in a text using the Rabin-Karp algorithm.
 * @param text The text to search in.
 * @param pattern The pattern to search for.
 * @return The index of the first occurrence of the pattern in the text or -1 if the pattern is not found. Also returns -1 in any of the corner cases (like empty pattern or text, pattern longer than text, etc.).
 */
int searchRabinKarp(const std::string& text, const std::string& pattern);

#endif // RABIN_KARP_LIB_HPP
