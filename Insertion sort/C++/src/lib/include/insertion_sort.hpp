#ifndef INSERTION_SORT_LIB_HPP
#define INSERTION_SORT_LIB_HPP

template <typename T>
void insertionSort(T* arr, const int n) {
    for (int i = 1; i < n; i++) {
        T temp = arr[i];
        int j = i;
        for (; j >= 1 && arr[j - 1] > temp; j--) {
            arr[j] = arr[j - 1];
        }
        arr[j] = temp;
    }
}

#endif // INSERTION_SORT_LIB_HPP
