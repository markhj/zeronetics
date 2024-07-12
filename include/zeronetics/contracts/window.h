#pragma once

#include "input-manager.h"
#include "zeronetics/core/inputs.h"
#include "zeronetics/core/settings.h"

#include <functional>
#include <memory>

namespace ZEN {
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
         * Callback when the window is closed.
         *
         * @param handle
         */
        virtual void onClose(std::function<void()> handle) = 0;

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
}
