#pragma once

#include "zeronetics/core/inputs.h"
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
         * Process events on every iteration of the loop.
         *
         * This can be used, among other things, to handle key-down states.
         *
         * @param delta
         */
        virtual void process(dt_float delta) = 0;

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
