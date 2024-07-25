#pragma once

#include <algorithm>
#include <string>

namespace ZEN {
    class Strings {
    public:
        /**
         * Convert a string to all lower-case characters.
         *
         * @ref helpers
         *
         * @param input
         * @return
         */
        static std::string toLowerCase(const std::string &input) noexcept;

        /**
         * Convert a string to all upper-case characters.
         *
         * @ref helpers
         *
         * @param input
         * @return
         */
        static std::string toUpperCase(const std::string &input) noexcept;
    };
}
