#include "knuth_morris_pratt.hpp"
#include <cstddef>
#include <memory>
#include <string>
#include <vector>


namespace {
    std::unique_ptr<std::size_t[]> createLPS(const std::string& pattern) {
        const std::size_t m = pattern.size();

        auto lps = std::make_unique<std::size_t[]>(m);
        lps[0] = 0;
        std::size_t i = 1;
        std::size_t len = 0;

        while (i < m) {
            if (pattern[i] == pattern[len]) {
                lps[i++] = ++len;
            } else {
                if (len != 0) {
                    len = lps[len - 1];
                } else {
                    lps[i++] = 0;
                }
            }
        }

        return lps;
    }
}  // namespace


std::vector<std::size_t> searchKMP(const std::string& text, const std::string& pattern) {
    const std::size_t n = text.size();
    const std::size_t m = pattern.size();

    if (m == 0) {
        return {0};
    }

    const auto lps = createLPS(pattern);
    std::vector<std::size_t> matches;
    std::size_t i = 0;
    std::size_t j = 0;

    while (i + (m - j) <= n) {
        if (text[i] == pattern[j]) {
            i++;
            j++;

            if (j == m) {
                matches.push_back(i - j);
                j = lps[j - 1];
            }
        } else {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }

    return matches;
}
