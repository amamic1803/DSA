#include "linked_list.hpp"
#include "tests.hpp"
#include <string>
#include <vector>

int main(const int argc, char *argv[]) {
    if (argc != 2) {
        return -2;
    }

    const std::string arg(argv[1]);
    bool test_result;

    if (arg == "seq1")
        test_result = test_seq1();
    else if (arg == "seq2")
        test_result = test_seq2();
    else if (arg == "seq3")
        test_result = test_seq3();
    else if (arg == "seq4")
        test_result = test_seq4();
    else if (arg == "seq5")
        test_result = test_seq5();
    else if (arg == "num1")
        test_result = test_num1();
    else if (arg == "num2")
        test_result = test_num2();
    else if (arg == "num3")
        test_result = test_num3();
    else if (arg == "num4")
        test_result = test_num4();
    else if (arg == "num5")
        test_result = test_num5();
    else if (arg == "num6")
        test_result = test_num6();
    else
        return -3;

    return test_result ? 0 : -1;
}

bool test_seq1() {
    const std::vector<unsigned long long> expected{0, 1, 1, 2, 3, 5, 8, 13, 21, 34};
    const auto result = fibonacciSequence(9);
    return result == expected;
}

bool test_seq2() {
    const std::vector<unsigned long long> expected{0};
    const auto result = fibonacciSequence(0);
    return result == expected;
}

bool test_seq3() {
    const std::vector<unsigned long long> expected{0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765};
    const auto result = fibonacciSequence(20);
    return result == expected;
}

bool test_seq4() {
    const std::vector<unsigned long long> expected{0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144};
    const auto result = fibonacciSequence(12);
    return result == expected;
}

bool test_seq5() {
    const std::vector<unsigned long long> expected{0, 1, 1, 2};
    const auto result = fibonacciSequence(3);
    return result == expected;
}

bool test_num1() {
    constexpr int expected = 21;
    const auto result1 = fibonacciNumber(8);
    const auto result2 = fibonacciNumberRecursive(8);
    return result1 == expected && result2 == expected;
}

bool test_num2() {
    constexpr int expected = 0;
    const auto result1 = fibonacciNumber(0);
    const auto result2 = fibonacciNumberRecursive(0);
    return result1 == expected && result2 == expected;
}

bool test_num3() {
    constexpr int expected = 6765;
    const auto result1 = fibonacciNumber(20);
    const auto result2 = fibonacciNumberRecursive(20);
    return result1 == expected && result2 == expected;
}

bool test_num4() {
    constexpr int expected = 144;
    const auto result1 = fibonacciNumber(12);
    const auto result2 = fibonacciNumberRecursive(12);
    return result1 == expected && result2 == expected;
}

bool test_num5() {
    constexpr int expected = 1;
    const auto result1 = fibonacciNumber(1);
    const auto result2 = fibonacciNumberRecursive(1);
    return result1 == expected && result2 == expected;
}

bool test_num6() {
    constexpr int expected = 75025;
    const auto result1 = fibonacciNumber(25);
    const auto result2 = fibonacciNumberRecursive(25);
    return result1 == expected && result2 == expected;
}
