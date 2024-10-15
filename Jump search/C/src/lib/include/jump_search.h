#ifndef JUMP_SEARCH_H
#define JUMP_SEARCH_H

/**
 * \brief Performs a jump search on a sorted array.
 *
 * This function searches for a target value within a sorted array using the jump search algorithm.
 *
 * \param arr The array to search.
 * \param size The number of elements in the array.
 * \param target The value to search for.
 * \return The index of the target value if found, otherwise -1.
 */
int jumpSearch(const int arr[], int size, int target);

#endif // JUMP_SEARCH_H
