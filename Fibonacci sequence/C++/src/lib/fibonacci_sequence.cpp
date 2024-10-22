#include "fibonacci_sequence.hpp"
#include <cmath>
#include <vector>

std::vector<unsigned long long> fibonacciSequence(const unsigned int n) {
    std::vector<unsigned long long> fibonacci_sequence;
    fibonacci_sequence.reserve(n + 1);

    switch (n) {
        case 0:
            fibonacci_sequence.push_back(0);
            break;
        case 1:
            fibonacci_sequence.push_back(0);
            fibonacci_sequence.push_back(1);
            break;
        default:
            fibonacci_sequence.push_back(0);
            fibonacci_sequence.push_back(1);
            for (int i = 2; i <= n; i++)
                fibonacci_sequence.push_back(fibonacci_sequence[i - 1] + fibonacci_sequence[i - 2]);
            break;
    }

    return fibonacci_sequence;
}

unsigned long long fibonacciNumber(const unsigned int n) {
    const double sqrt5 = sqrt(5);
    return static_cast<unsigned long long>(round((pow(1 + sqrt5, n) - pow(1 - sqrt5, n)) / (sqrt5 * pow(2, n))));
}

unsigned long long fibonacciNumberRecursive(const unsigned int n) {
    switch (n) {
        case 0:
            return 0;
        case 1:
            return 1;
        default:
            unsigned long long Fn_2 = 0;
            unsigned long long Fn_1 = 1;
            unsigned long long Fn = Fn_1 + Fn_2;

            for (int i = 2; i < n; i++) {
                Fn_2 = Fn_1;
                Fn_1 = Fn;
                Fn = Fn_1 + Fn_2;
            }

            return Fn;
    }
}
