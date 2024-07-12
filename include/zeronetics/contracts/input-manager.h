#pragma once

#include "zeronetics/core/input.h"
#include "zeronetics/core/settings.h"

#include <memory>

namespace ZEN {
    /**
     * Interface for an object which can be connected to a window
     * in order to handle various user inputs such as key presses
     * and mouse movement.
     */
    class IInputManager {
    public:
        /**
         * Handle for when a key is pressed or released.
         *
         * @param keyEvent Informs the key state, the pressed key, etc.
         */
        virtual void onKeyStateChanged(const KeyStateEvent &keyEvent) = 0;

        /**
         * Handle for when the mouse cursor has been moved.
         *
         * @param mouseMovedEvent
         */
        virtual void onMouseMoved(const MouseMovedEvent &mouseMovedEvent) = 0;
    };
}
