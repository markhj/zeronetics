#pragma once

#include "zeronetics/core/settings.h"
#include "zeronetics/core/controls.h"

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
        virtual void onKeyStateChanged(const KeyEvent &keyEvent) = 0;

    };

    /**
     * Contract for a window implementation which is used in various
     * parts of the engine.
     */
    class IWindow {
    public:
        /**
         * Handle the initial generation of the window.
         *
         * @param settings
         */
        virtual void generate(const Settings &settings) noexcept(false) = 0;

        /**
         * Handle a re-generation of the window, when video settings
         * have changed.
         *
         * @param settings
         */
        virtual void regenerate(const Settings &settings) noexcept(false) = 0;

        /**
         * Request the window to close.
         */
        virtual void close() noexcept = 0;

        /**
         * Process user inputs.
         */
        virtual inline void handleInputs() = 0;

        /**
         * Swap buffers.
         */
        virtual inline void handleBuffer() = 0;

        /**
         * Set (or replace) the Input Manager.
         */
        virtual void setInputManager(const std::shared_ptr<IInputManager> &inputManager) = 0;

    };

    /**
     * Contract for renderers.
     */
    class IRenderer {

    };
}
