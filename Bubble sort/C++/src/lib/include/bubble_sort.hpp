#ifndef BUBBLE_SORT_LIB_HPP
#define BUBBLE_SORT_LIB_HPP

template <typename T>
void bubbleSort(T* arr, const int n) {
    bool changed = true;
    for (int i = 0; changed; i++) {
        changed = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j + 1] < arr[j]) {
                T temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                changed = true;
            }
        }
    }
}

#endif // BUBBLE_SORT_LIB_HPP
