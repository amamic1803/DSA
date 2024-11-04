#ifndef SELECTION_SORT_LIB_HPP
#define SELECTION_SORT_LIB_HPP

template <typename T>
void selectionSort(T* arr, const int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        if (min != i) {
            T temp = arr[i];
            arr[i] = arr[min];
            arr[min] = temp;
        }
    }
}

#endif // SELECTION_SORT_LIB_HPP
