#include "knuth_morris_pratt.hpp"
#include "tests.hpp"
#include <cstddef>
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
        case 8:
            test_result = test_8();
            break;
        case 9:
            test_result = test_9();
            break;
        case 10:
            test_result = test_10();
            break;
        default:
            return -6;
    }

    return test_result ? 0 : -1;
}
// NOLINTEND(bugprone-exception-escape)

bool test_1() {
    const std::vector<std::size_t> expected{0};
    const std::vector<std::size_t> result = searchKMP("", "");
    return result == expected;
}

bool test_2() {
    const std::vector<std::size_t> expected;
    const std::vector<std::size_t> result = searchKMP("", "pattern");
    return result == expected;
}

bool test_3() {
    const std::vector<std::size_t> expected{0};
    const std::vector<std::size_t> result = searchKMP("text", "");
    return result == expected;
}

bool test_4() {
    const std::vector<std::size_t> expected;
    const std::vector<std::size_t> result = searchKMP("short", "longerpattern");
    return expected == result;
}

bool test_5() {
    const std::vector<std::size_t> expected{0};
    const std::vector<std::size_t> result = searchKMP("pattern", "pattern");
    return result == expected;
}

bool test_6() {
    const std::vector<std::size_t> expected{0};
    const std::vector<std::size_t> result = searchKMP("pattern in text", "pattern");
    return result == expected;
}

bool test_7() {
    const std::vector<std::size_t> expected{10};
    const std::vector<std::size_t> result = searchKMP("text with pattern", "pattern");
    return result == expected;
}

bool test_8() {
    const std::vector<std::size_t> expected{10, 22};
    const std::vector<std::size_t> result = searchKMP("text with pattern and pattern", "pattern");
    return result == expected;
}

bool test_9() {
    const std::vector<std::size_t> expected;
    const std::vector<std::size_t> result = searchKMP("clean text", "pattern");
    return result == expected;
}

bool test_10() {
    const std::vector<std::size_t> expected{15};
    const std::vector<std::size_t> result = searchKMP("long text with pattern in the middle", "pattern");
    return result == expected;
}
