#include "rabin_karp.hpp"
#include <cstddef>
#include <string>


namespace {
    const int BASE = 256;
    const int MOD = 251;

    int getHash(const std::string& str, const size_t length) {
        int hash = 0;
        for (size_t i = 0; i < length; i++) {
            hash = (hash * BASE + str[i]) % MOD;
        }
        return hash;
    }

    int reHash(const int old_hash, const char old_char, const char new_char, const int leading_power) {
        int new_hash = old_hash;
        new_hash -= old_char * leading_power;
        new_hash *= BASE;
        new_hash = (new_hash + new_char) % MOD;
        if (new_hash < 0) {
            new_hash += MOD;
        }
        return new_hash;
    }

    int calculateLeadingPower(const size_t length) {
        int power = 1;
        for (size_t i = 1; i < length; i++) {
            power = (power * BASE) % MOD;
        }
        return power;
    }
}  // namespace


int searchRabinKarp(const std::string& text, const std::string& pattern) {
    const size_t n = text.size();
    const size_t m = pattern.size();

    if (n == 0 || m == 0 || n < m) {
        return -1;
    }

    int moving_hash = getHash(text, m);
    const int pattern_hash = getHash(pattern, m);
    const int leading_power = calculateLeadingPower(m);

    for (size_t i = 0; i <= n - m; i++) {
        if (pattern_hash == moving_hash) {
            size_t j = 0;
            for (; j < m; j++) {
                if (text[i + j] != pattern[j]) {
                    break;
                }
            }
            if (j == m) {
                return static_cast<int>(i);
            }
        }
        if (i < n - m) {
            moving_hash = reHash(moving_hash, text[i], text[i + m], leading_power);
        }
    }

    return -1;
}
