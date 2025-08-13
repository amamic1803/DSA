#include "binary_search.h"

int binarySearch(const int target, const int arr[], const int size) {
    // Explicitly handle the case where the array is empty, suppressing a compiler warning
    if (size == 0) {
        return -1;
    }

    int low = 0;
    int high = size - 1;

    while (low <= high) {
        const int mid = low + (high - low) / 2;
        if (arr[mid] == target) {
            return mid;
        }
        if (target < arr[mid]) {
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }

    return -1;
}
