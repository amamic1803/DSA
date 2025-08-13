#ifndef BINARY_SEARCH_H
#define BINARY_SEARCH_H

/**
 * \brief Performs a binary search on a sorted array.
 *
 * This function searches for a target value within a sorted array using the binary search algorithm.
 *
 * \param target The value to search for.
 * \param arr The array to search.
 * \param size The number of elements in the array.
 * \return The index of the target value if found, otherwise -1.
 */
int binarySearch(int target, const int arr[], int size);

#endif // BINARY_SEARCH_H
