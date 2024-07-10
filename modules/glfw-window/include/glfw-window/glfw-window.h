#pragma once

#include "zeronetics/contracts/contracts.h"

namespace ZEN {
    class Window : public IWindow {
    public:
        ~Window();

        void generate(const Settings &settings) noexcept(false) override;

        void regenerate(const Settings &settings) noexcept(false) override;

        void close() noexcept override;

        /**
         * Process user inputs.
         */
        void handleInputs() override;

        /**
         * Swap buffers.
         */
        void handleBuffer() override;


    };
}
