#include "zeronetics/helpers/strings.h"
#include <functional>

namespace {
    inline std::string characterIter(const std::string &input,
                                     const std::function<unsigned char(unsigned char)> &algo) noexcept {
        std::string result = input;
        std::transform(result.begin(),
                       result.end(),
                       result.begin(),
                       [&](unsigned char c) -> unsigned char {
                           return algo(c);
                       });
        return result;
    }
}

std::string ZEN::Strings::toLowerCase(const std::string &input) noexcept {
    return characterIter(input, [](unsigned char c) -> unsigned char {
        return std::tolower(c);
    });
}

std::string ZEN::Strings::toUpperCase(const std::string &input) noexcept {
    return characterIter(input, [](unsigned char c) -> unsigned char {
        return std::toupper(c);
    });
}
