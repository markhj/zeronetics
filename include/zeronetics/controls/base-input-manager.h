#pragma once

#include "zeronetics/contracts/window.h"

namespace ZEN {
    /**
     * A class that implements empty versions of the required methods
     * in ZEN::IInputManager, making it easier for users to get started
     * and/or to work with an implementation that require only few methods.
     */
    class BaseInputManager : public IInputManager {
        /**
         * Process events on every iteration of the loop.
         *
         * This can be used, among other things, to handle key-down states.
         *
         * @param delta
         */
        void process(dt_float delta) override {}

        /**
         * Handle for when a key state is changed.
         *
         * @param keyEvent
         */
        void onKeyStateChanged(const KeyStateEvent &keyEvent) override {}

        /**
         * Handle for when the mouse cursor has moved.
         *
         * @param mouseMovedEvent
         */
        void onMouseMoved(const MouseMovedEvent &mouseMovedEvent) override {}
    };
}
