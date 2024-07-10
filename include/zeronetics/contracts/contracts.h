#pragma once

#include "zeronetics/core/settings.h"

namespace ZEN {
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

    };

    class IRenderer {

    };
}
