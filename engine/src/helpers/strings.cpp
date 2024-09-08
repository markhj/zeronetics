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

std::string ZEN::Strings::replace(const std::string &target,
                                  const std::string &find,
                                  const std::string &replace) noexcept {
    std::string result = target;
    size_t startPos = 0;

    if (find.empty()) {
        return result;
    }

    while ((startPos = result.find(find, startPos)) != std::string::npos) {
        result.replace(startPos, find.length(), replace);
        startPos += replace.length();
    }

    return result;
}
