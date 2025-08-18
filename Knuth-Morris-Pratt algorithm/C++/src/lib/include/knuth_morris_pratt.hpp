#ifndef KNUTH_MORRIS_PRATT_LIB_HPP
#define KNUTH_MORRIS_PRATT_LIB_HPP

#include <cstddef>
#include <string>
#include <vector>

/**
 * @brief Search for a pattern in a text using the Knuth-Morris-Pratt algorithm.
 * @param text The text to search in.
 * @param pattern The pattern to search for.
 * @return The vector with indices of the occurrences of the pattern in the text.
 *         If there are no occurrences of the pattern in the text, an empty vector is returned.
 *         If the pattern is an empty string, only the match at index 0 is returned.
 */
std::vector<std::size_t> searchKMP(const std::string& text, const std::string& pattern);

#endif // KNUTH_MORRIS_PRATT_LIB_HPP
