#ifndef QUICKSORT_LIB_HPP
#define QUICKSORT_LIB_HPP

template <typename T>
static void insertionSort(T* arr, const int n) {
    if (n < 2)
        return;
    for (int i = 1; i < n; i++) {
        T tmp = arr[i];
        int j;
        for (j = i; j >= 1 && arr[j - 1] > tmp; j--)
            arr[j] = arr[j - 1];
        arr[j] = tmp;
    }
}

template <typename T>
static void swap(T* a, T* b) {
    T temp = *a;
    *a = *b;
    *b = temp;
}

template <typename T>
void quicksort(T* arr, const int n) {
    // cutoff to insertion sort
    if (n < 10) {
        insertionSort(arr, n);
        return;
    }

    // median-of-three
    const int mid = n >> 1;
    if (arr[0] > arr[mid])
        swap(&arr[0], &arr[mid]);
    if (arr[0] > arr[n - 1])
        swap(&arr[0], &arr[n - 1]);
    if (arr[mid] > arr[n - 1])
        swap(&arr[mid], &arr[n - 1]);

    // place pivot at position n - 2
    swap(&arr[mid], &arr[n - 2]);

    // partition
    const int pivot = arr[n - 2];
    int i = 0;
    int j = n - 2;
    while (true) {
        while (arr[++i] < pivot);
        while (arr[--j] > pivot);
        if (i >= j) break;
        swap(&arr[i], &arr[j]);
    }

    // restore pivot
    swap(&arr[i], &arr[n - 2]);

    // recursively sort partitions
    quicksort(arr, i);
    quicksort(&arr[i + 1], n - i - 1);
}

#endif // QUICKSORT_LIB_HPP
