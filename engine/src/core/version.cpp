#include "zeronetics/core/version.h"
#include <format>

std::string ZEN::Version::toSemVer() {
    if (preview.has_value()) {
        auto prev = preview.value();
        return std::format("{}.{}.{}-{}.{}", major, minor, patch, prev.label, prev.version);
    } else {
        return std::format("{}.{}.{}", major, minor, patch);
    }
}
