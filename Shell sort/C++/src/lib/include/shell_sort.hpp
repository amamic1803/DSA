#ifndef SHELL_SORT_LIB_HPP
#define SHELL_SORT_LIB_HPP

template <typename T>
void shellSort(T* arr, const int n) {
    if (n < 2) {
        return;
    }
    for (int k = n / 2; k > 0; k /= 2) {
        for (int i = k; i < n; i++) {
            T tmp = arr[i];
            int j = i;
            for (; j >= k && arr[j - k] > tmp; j -= k) {
                arr[j] = arr[j - k];
            }
            arr[j] = tmp;
        }
    }
}

#endif // SHELL_SORT_LIB_HPP
