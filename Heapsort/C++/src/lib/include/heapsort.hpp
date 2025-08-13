#ifndef HEAPSORT_LIB_HPP
#define HEAPSORT_LIB_HPP

#include <utility>


template <typename T>
void swap(const int i, const int j, T* arr) {
    T temp = std::move(arr[i]);
    arr[i] = std::move(arr[j]);
    arr[j] = std::move(temp);

}

template <typename T>
void heapify(int node, T* arr, int n) {
    const int left = (node * 2) + 1;
    const int right = (node * 2) + 2;

    int largest = node;
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != node) {
        swap(largest, node, arr);
        heapify(largest, arr, n);
    }
}

template <typename T>
void heapsort(T* arr, int n) {
    // construct heap
    for (int i = (n / 2) - 1; i >= 0; i--) {
        heapify(i, arr, n);
    }

    // perform heapsort (popping a max element and storing it at the end of an array)
    while (n > 1) {
        swap(0, n - 1, arr);
        heapify(0, arr, n - 1);
        n--;
    }
}

#endif // HEAPSORT_LIB_HPP
