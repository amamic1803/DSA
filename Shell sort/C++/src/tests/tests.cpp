#include "shell_sort.hpp"
#include "tests.hpp"
#include <stdexcept>
#include <string>
#include <vector>

// NOLINTBEGIN(bugprone-exception-escape)
int main(const int argc, char *argv[]) {
    if (argc != 2) {
        return -2;
    }

    int problem_number = 0;
    try {
        problem_number = std::stoi(argv[1]);
    } catch (std::invalid_argument &_) {
        return -3;
    } catch (std::out_of_range &_) {
        return -4;
    } catch (...) {
        return -5;
    }

    bool test_result = false;
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
        case 6:
            test_result = test_6();
            break;
        case 7:
            test_result = test_7();
            break;
        default:
            return -6;
    }

    return test_result ? 0 : -1;
}
// NOLINTEND(bugprone-exception-escape)

bool test_1() {
    std::vector<int> arr = {};
    shellSort(arr.data(), static_cast<int>(arr.size()));
    return arr.empty();
}

bool test_2() {
    std::vector<int> arr{1};
    shellSort(arr.data(), static_cast<int>(arr.size()));
    return arr == std::vector<int>{1};
}

bool test_3() {
    std::vector<int> arr{1, 2, 3, 4, 5};
    shellSort(arr.data(), static_cast<int>(arr.size()));
    return arr == std::vector<int>{1, 2, 3, 4, 5};
}

bool test_4() {
    std::vector<int> arr{5, 4, 3, 2, 1};
    shellSort(arr.data(), static_cast<int>(arr.size()));
    return arr == std::vector<int>{1, 2, 3, 4, 5};
}

bool test_5() {
    std::vector<int> arr{3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    shellSort(arr.data(), static_cast<int>(arr.size()));
    return arr == std::vector<int>{1, 1, 2, 3, 3, 4, 5, 5, 5, 6, 9};
}

bool test_6() {
    std::vector<int> arr{3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 8, 9, 7, 9, 3};
    shellSort(arr.data(), static_cast<int>(arr.size()));
    return arr == std::vector<int>{1, 1, 2, 3, 3, 3, 4, 5, 5, 5, 6, 7, 8, 9, 9, 9};
}

bool test_7() {
    std::vector<int> arr{3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 8, 9, 7, 9, 3, 2, 3, 8, 4, 6, 2, 6, 4, 3, 3};
    shellSort(arr.data(), static_cast<int>(arr.size()));
    return arr == std::vector<int>{1, 1, 2, 2, 2, 3, 3, 3, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 8, 8, 9, 9, 9};
}
