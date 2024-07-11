#include "zeronetics/core/controls.h"

std::unordered_map<int, ZEN::Key> ZEN::KeyMap::map = {
        {65, Key::A},
        {256, Key::Esc},
};

std::optional<ZEN::Key> ZEN::KeyMap::toKey(int key) {
    if (map.contains(key)) {
        return map.at(key);
    }
    return std::nullopt;
}

std::optional<int> ZEN::KeyMap::toInt(const ZEN::Key &key) {
    for (const auto &other: map) {
        if (other.second == key) {
            return other.first;
        }
    }
    return std::nullopt;
}
