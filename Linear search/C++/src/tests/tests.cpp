#include "linear_search.hpp"
#include "tests.hpp"
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
    const std::vector v{1, 2, 3, 4, 5};
    return linear_search(v.data(), static_cast<int>(v.size()), 3) == 2;
}

bool test_2() {
    const std::vector v{1, 2, 3, 4, 5};
    return linear_search(v.data(), static_cast<int>(v.size()), 6) == -1;
}

bool test_3() {
    const std::vector v{1, 2, 3, 4, 5};
    return linear_search(v.data(), static_cast<int>(v.size()), 1) == 0;
}

bool test_4() {
    const std::vector v{1, 2, 3, 4, 5};
    return linear_search(v.data(), static_cast<int>(v.size()), 5) == 4;
}

bool test_5() {
    const std::vector v{1, 2, 3, 4, 5};
    return linear_search(v.data(), static_cast<int>(v.size()), 2) == 1;
}
