#pragma once

#include <optional>
#include <unordered_map>

namespace ZEN {
    /**
     * List of supported keys (and their number)
     *
     * @important For developers: When more keys have been added to this enum,
     *      they must accordingly be added to EnumMapping.
     */
    enum class Key {
        A = 65,
        B = 66,
        C = 67,
        D = 68,
        E = 69,
        F = 70,
        G = 71,
        H = 72,
        I = 73,
        J = 74,
        K = 75,
        L = 76,
        M = 77,
        N = 78,
        O = 79,
        P = 80,
        Q = 81,
        R = 82,
        S = 83,
        T = 84,
        U = 85,
        V = 86,
        W = 87,
        X = 88,
        Y = 89,
        Z = 90,

        F1 = 290,
        F2 = 291,
        F3 = 292,
        F4 = 293,
        F5 = 294,
        F6 = 295,
        F7 = 296,
        F8 = 297,
        F9 = 298,
        F10 = 299,
        F11 = 300,
        F12 = 301,

        No0 = 48,
        No1 = 49,
        No2 = 50,
        No3 = 51,
        No4 = 52,
        No5 = 53,
        No6 = 54,
        No7 = 55,
        No8 = 56,
        No9 = 57,

        Enter = 257,
        Tab = 258,
        Backspace = 259,
        LeftShift = 340,
        RightShift = 344,
        LeftCtrl = 341,
        LeftAlt = 342,
        RightCtrl = 345,
        AltGr = 346,
        Space = 32,
        Esc = 256,
    };

    /**
     * Struct that helps retrieving keys based on integer values.
     */
    struct KeyMap {
    public:
        /**
         * Convert an ASCII value to a ZEN::Key.
         *
         * If the value isn't mapped to a key, ``std::nullopt``
         * will be returned.
         *
         * @param key
         * @return
         */
        static std::optional<Key> toKey(int key);

        /**
         * Convert a ZEN::Key to its corresponding ASCII value.
         *
         * @param key
         * @return
         */
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
