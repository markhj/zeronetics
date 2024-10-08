#pragma once

#include "zeronetics/contracts/window.h"

namespace ZEN {
    /**
     * Implementation of the ZEN::IWindow with GLFW.
     */
    class Window : public IWindow {
    public:
        /**
         * The title displayed in the window bar frame.
         */
        const char *windowTitle = "Zeronetics Game";

        /**
         * Destructor.
         *
         * Terminates GLFW.
         */
        ~Window();

        /**
         * Generate the GLFW window with the supplied settings.
         *
         * @param settings
         *
         * @ref settings
         */
        void generate(const Settings &settings) noexcept(false) override;

        /**
         * Re-generate the window (typically, when video settings
         * have changed).
         *
         * @param settings
         *
         * @ref settings
         */
        void regenerate(const Settings &settings) noexcept(false) override;

        /**
         * Close GLFW window.
         */
        void close() noexcept override;

        /**
         * Set the callback for when the window closes.
         *
         * @param handle
         */
        void onClose(std::function<void()> handle) override;

        /**
         * Callback when the window is resized.
         *
         * @param handle
         */
        void onResize(std::function<void()> handle) override;

        /**
         * Process user inputs.
         */
        inline void handleInputs() override;

        /**
         * Swap buffers.
         */
        inline void handleBuffer() override;

        /**
         * Process to be run on every game loop iteration.
         *
         * @param delta
         */
        void process(dt_float delta) override;

        /**
         * Set (or replace) the Input Manager.
         *
         * @param inputManager
         */
        void setInputManager(const std::shared_ptr<IInputManager> &inputManager) override;

    };
}
