#include "insertion_sort.hpp"
#include "tests.hpp"
#include <algorithm>
#include <stdexcept>
#include <string>
#include <vector>

int main(const int argc, char *argv[]) {
    if (argc != 2) {
        return -2;
    }

    int problem_number;
    try {
        problem_number = std::stoi(argv[1]);
    } catch (std::invalid_argument &_) {
        return -3;
    } catch (std::out_of_range &_) {
        return -4;
    } catch (...) {
        return -5;
    }

    bool test_result;
    switch (problem_number) {
        case 1:
            test_result = test_1();
            break;
        case 2:
            test_result = test_2();
            break;
        case 3:
            test_result = test_3();
            break;
        case 4:
            test_result = test_4();
            break;
        case 5:
            test_result = test_5();
            break;
        default:
            return -6;
    }

    return test_result ? 0 : -1;
}

bool test_1() {
    std::vector arr{5, 4, 3, 2, 1};
    insertionSort(arr.data(), static_cast<int>(arr.size()));
    return std::is_sorted(arr.begin(), arr.end());
}
bool test_2() {
    std::vector arr{1, 2, 3, 4, 5};
    insertionSort(arr.data(), static_cast<int>(arr.size()));
    return std::is_sorted(arr.begin(), arr.end());
}
bool test_3() {
    std::vector arr = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    insertionSort(arr.data(), static_cast<int>(arr.size()));
    return std::is_sorted(arr.begin(), arr.end());
}
bool test_4() {
    std::vector arr{10, -1, 2, 5, 0};
    insertionSort(arr.data(), static_cast<int>(arr.size()));
    return std::is_sorted(arr.begin(), arr.end());
}
bool test_5() {
    std::vector<int> arr{};
    insertionSort(arr.data(), static_cast<int>(arr.size()));
    return std::is_sorted(arr.begin(), arr.end());
}