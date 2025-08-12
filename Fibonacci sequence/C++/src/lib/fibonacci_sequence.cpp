#include "fibonacci_sequence.hpp"
#include <cmath>
#include <cstdint>
#include <vector>

std::vector<int64_t> fibonacciSequence(const int n) {
    std::vector<int64_t> fibonacci_sequence;
    fibonacci_sequence.reserve(n + 1);

    if (n < 0) {
        return fibonacci_sequence; // Return empty vector for negative n
    }

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
            for (int i = 2; i <= n; i++) {
                fibonacci_sequence.push_back(fibonacci_sequence[i - 1] + fibonacci_sequence[i - 2]);
            }
            break;
    }

    return fibonacci_sequence;
}

int64_t fibonacciNumber(const int n) {
    const double sqrt5 = sqrt(5);
    return static_cast<int64_t>(round((pow(1 + sqrt5, n) - pow(1 - sqrt5, n)) / (sqrt5 * pow(2, n))));
}

int64_t fibonacciNumberRecursive(const int n) {
    switch (n) {
        case 0:
            return 0;
        case 1:
            return 1;
        default:
            int64_t Fn_2 = 0;
            int64_t Fn_1 = 1;
            int64_t Fn = Fn_1 + Fn_2;

            for (int i = 2; i < n; i++) {
                Fn_2 = Fn_1;
                Fn_1 = Fn;
                Fn = Fn_1 + Fn_2;
            }

            return Fn;
    }
}
