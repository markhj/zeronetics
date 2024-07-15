#pragma once

#include "zeronetics/contracts/input-manager.h"

namespace ZEN::ControlSystems {
    /**
     * A more fully-fledged implementation of ZEN::IInputManager, which
     * helps you manage a wider range of controls "out of the box",
     * utilizing an easy mapping system.
     */
    class ControlManager : public IInputManager {
    public:
        /**
         * Handle for when a key state is changed.
         *
         * @param keyEvent
         */
        void onKeyStateChanged(const KeyStateEvent &keyEvent) override;

        /**
         * Handle for when the mouse cursor has moved.
         *
         * @param mouseMovedEvent
         */
        void onMouseMoved(const MouseMovedEvent &mouseMovedEvent) override;
    };
}
