#include "knuth_morris_pratt.hpp"
#include "tests.hpp"
#include <stdexcept>
#include <string>

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

bool test_1() {
    return searchKnuthMorrisPratt("", "") == -1;
}

bool test_2() {
    return searchKnuthMorrisPratt("", "pattern") == -1;
}

bool test_3() {
    return searchKnuthMorrisPratt("text", "") == -1;
}

bool test_4() {
    return searchKnuthMorrisPratt("short", "longerpattern") == -1;
}

bool test_5() {
    return searchKnuthMorrisPratt("pattern", "pattern") == 0;
}

bool test_6() {
    return searchKnuthMorrisPratt("pattern in text", "pattern") == 0;
}

bool test_7() {
    return searchKnuthMorrisPratt("text with pattern", "pattern") == 10;
}

bool test_8() {
    return searchKnuthMorrisPratt("text with pattern and pattern", "pattern") == 10;
}

bool test_9() {
    return searchKnuthMorrisPratt("clean text", "pattern") == -1;
}

bool test_10() {
    return searchKnuthMorrisPratt("long text with pattern in the middle", "pattern") == 15;
}
