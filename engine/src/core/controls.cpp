#include "zeronetics/core/input.h"

std::unordered_map<int, ZEN::Key> ZEN::KeyMap::map = {
        {65, Key::A},
        {66, Key::B},
        {67, Key::C},
        {68, Key::D},
        {69, Key::E},
        {70, Key::F},
        {71, Key::G},
        {72, Key::H},
        {73, Key::I},
        {74, Key::J},
        {75, Key::K},
        {76, Key::L},
        {77, Key::M},
        {78, Key::N},
        {79, Key::O},
        {80, Key::P},
        {81, Key::Q},
        {82, Key::R},
        {83, Key::S},
        {84, Key::T},
        {85, Key::U},
        {86, Key::V},
        {87, Key::W},
        {88, Key::X},
        {89, Key::Y},
        {90, Key::Z},

        {290, Key::F1},
        {291, Key::F2},
        {292, Key::F3},
        {293, Key::F4},
        {294, Key::F5},
        {295, Key::F6},
        {296, Key::F7},
        {297, Key::F8},
        {298, Key::F9},
        {299, Key::F10},
        {300, Key::F11},
        {301, Key::F12},

        {48, Key::No0},
        {49, Key::No1},
        {50, Key::No2},
        {51, Key::No3},
        {52, Key::No4},
        {53, Key::No5},
        {54, Key::No6},
        {55, Key::No7},
        {56, Key::No8},
        {57, Key::No9},

        {257, Key::Enter},
        {258, Key::Tab},
        {259, Key::Backspace},
        {340, Key::LeftShift},
        {344, Key::RightShift},
        {341, Key::LeftCtrl},
        {342, Key::LeftAlt},
        {345, Key::RightCtrl},
        {346, Key::AltGr},
        {32, Key::Space},

        {256, Key::Esc}};

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
