#include "jump_search.h"
#include <math.h>

int jumpSearch(const int arr[], const int size, const int target) {
    // Explicitly handle the case where the array is empty, suppressing a compiler warning
    if (size == 0) {
        return -1;
    }

    const int blockSize = (int) ceil(sqrt(size));
    int blockStart = 0;

    while (blockStart < size && arr[blockStart] <= target) {
        blockStart += blockSize;
    }
    blockStart -= blockSize;

    const int blockEnd = blockStart + blockSize < size ? blockStart + blockSize : size;

    for (int i = blockStart; i < blockEnd; i++) {
        if (arr[i] == target) {
            return i;
        }
        if (arr[i] > target) {
            break;
        }
    }

    return -1;
}
