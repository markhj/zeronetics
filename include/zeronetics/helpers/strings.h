#pragma once

#include <algorithm>
#include <string>

namespace ZEN {
    /**
     * Convert a string to all lower-case characters.
     *
     * @ref helpers
     *
     * @param input
     * @return
     */
    std::string toLowerCase(const std::string &input) noexcept {
        std::string result = input;
        std::transform(result.begin(), result.end(), result.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        return result;
    }

    /**
     * Convert a string to all upper-case characters.
     *
     * @ref helpers
     *
     * @param input
     * @return
     */
    std::string toUpperCase(const std::string &input) noexcept {
        std::string result = input;
        std::transform(result.begin(), result.end(), result.begin(),
                       [](unsigned char c) { return std::toupper(c); });
        return result;
    }
}
