#include "knuth_morris_pratt.hpp"
#include <cstddef>
#include <memory>
#include <string>


namespace {
    size_t longestPrefixSuffix(const std::string& pattern, const size_t size) {
        size_t longest = 0;

        for (size_t length = 1; length < size; length++) {
            size_t i;
            for (i = 0; i < length; i++) {
                if (pattern[i] != pattern[size - length + i]) {
                    break;
                }
            }
            if (i == length) {
                longest = length;
            }
        }

        return longest;
    }

    std::unique_ptr<size_t[]> createLPS(const std::string& pattern) {
        auto lps = std::make_unique<size_t[]>(pattern.size());

        for (size_t size = 1; size <= pattern.size(); size++) {
            lps[size - 1] = longestPrefixSuffix(pattern, size);
        }

        return lps;
    }
}


int searchKnuthMorrisPratt(const std::string& text, const std::string& pattern) {
    const size_t n = text.size();
    const size_t m = pattern.size();

    if (n == 0 || m == 0 || n < m) {
        return -1;
    }

    const std::unique_ptr<size_t[]> lps = createLPS(pattern);

    size_t i = 0;
    while (i <= n - m) {
        size_t j;
        for (j = 0; j < m; j++) {
            if (text[i + j] != pattern[j]) {
                break;
            }
        }
        if (j == m) {
            return static_cast<int>(i);
        }
        if (j == 0) {
            i++;
        } else {
            i += j - lps[j - 1];
        }
    }

    return -1;
}
