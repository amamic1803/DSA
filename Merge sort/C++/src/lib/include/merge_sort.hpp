#ifndef MERGE_SORT_LIB_HPP
#define MERGE_SORT_LIB_HPP

#include <algorithm>

template <typename T>
static void mergeSortRec(T* arr, const int n, T* tmp_arr) {
    if (n < 2)
        return;

    const int mid = n >> 1;
    mergeSortRec(arr, mid, tmp_arr);
    mergeSortRec(&arr[mid], n - mid, tmp_arr);

    int i = 0;
    int j = mid;
    int k = 0;
    while (i != mid && j != n)
        tmp_arr[k++] = arr[i] <= arr[j] ? arr[i++] : arr[j++];

    if (i != mid) {
        std::copy(&arr[i], &arr[mid], &tmp_arr[k]);
    } else if (j != n) {
        std::copy(&arr[j], &arr[n], &tmp_arr[k]);
    }

    std::copy(tmp_arr, tmp_arr + n, arr);
}

template <typename T>
void mergeSort(T* arr, const int n) {
    T* tmp_arr = new T[n];
    mergeSortRec(arr, n, tmp_arr);
    delete[] tmp_arr;
}

#endif // MERGE_SORT_LIB_HPP
