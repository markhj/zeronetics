#pragma once

#include "typedefs.h"
#include "enums.h"
#include <array>
#include <cstdint>
#include <optional>
#include <unordered_map>

namespace ZEN {
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
    struct KeyStateEvent {
        KeyState keyState;
        Key key;
    };

    /**
     * Mouse position
     */
    struct MousePosition {
        /**
         * X- and Y-axis of the cursor.
         */
        mouse_pos_axis x, y;
    };

    /**
     * When the mouse has moved, the absolute position
     * as well as relative position are reported.
     * The relative position is the movement since
     * last event reporting.
     */
    struct MouseMovedEvent {
        /**
         * Current position (within the window).
         */
        MousePosition position;

        /**
         * Change in position since last event reporting.
         */
        MousePosition relative;
    };
}
