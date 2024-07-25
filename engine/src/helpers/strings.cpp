#include "zeronetics/helpers/strings.h"

std::string ZEN::Strings::toLowerCase(const std::string &input) noexcept {
    std::string result = input;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return result;
}

std::string ZEN::Strings::toUpperCase(const std::string &input) noexcept {
    std::string result = input;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c) { return std::toupper(c); });
    return result;
}
