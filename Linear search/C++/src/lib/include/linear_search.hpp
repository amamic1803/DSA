#ifndef LINEAR_SEARCH_LIB_HPP
#define LINEAR_SEARCH_LIB_HPP

template <typename T>
int linear_search(const T *arr, const int size, const T& key) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == key) {
            return i;
        }
    }
    return -1;
}

#endif // LINEAR_SEARCH_LIB_HPP
