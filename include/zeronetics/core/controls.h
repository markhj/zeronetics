#pragma once

#include <optional>
#include <unordered_map>

namespace ZEN {
    enum class Key {
        A = 65,
        Esc = 256,
    };

    struct KeyMap {
    public:
        static std::optional<Key> toKey(int key);

        static std::optional<int> toInt(const Key &key);

    private:
        static std::unordered_map<int, Key> map;
    };

    enum class KeyState {
        JustPressed,
        JustReleased,
    };

    struct KeyEvent {
        KeyState keyState;
        Key key;
    };
}
