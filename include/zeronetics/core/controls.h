#pragma once

#include <optional>
#include <unordered_map>

namespace ZEN {
    /**
     * List of supported keys (and their number)
     */
    enum class Key {
        A = 65,
        Esc = 256,
    };

    /**
     * Struct that helps retrieving keys based on integer values.
     */
    struct KeyMap {
    public:
        static std::optional<Key> toKey(int key);

        static std::optional<int> toInt(const Key &key);

    private:
        static std::unordered_map<int, Key> map;
    };

    /**
     * Indicates if a key has just been pressed,
     * or just been released.
     *
     * @note Key down is different mechanism.
     */
    enum class KeyState {
        JustPressed,
        JustReleased,
    };

    /**
     * When the state of a key has changed.
     *
     * For instance, if "A" has just been pressed, or
     * if "ESC" has just been released.
     */
    struct KeyEvent {
        KeyState keyState;
        Key key;
    };
}
