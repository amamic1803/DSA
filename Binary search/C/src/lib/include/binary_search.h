#ifndef BINARY_SEARCH_H
#define BINARY_SEARCH_H

/**
 * \brief Performs a binary search on a sorted array.
 *
 * This function searches for a target value within a sorted array using the binary search algorithm.
 *
 * \param arr The array to search.
 * \param size The number of elements in the array.
 * \param target The value to search for.
 * \return The index of the target value if found, otherwise -1.
 */
int binarySearch(const int arr[], int size, int target);

#endif // BINARY_SEARCH_H
