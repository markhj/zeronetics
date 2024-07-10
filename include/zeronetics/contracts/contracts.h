#pragma once

#include "zeronetics/core/settings.h"

namespace ZEN {
    class IWindow {
    public:
        virtual void generate(const Settings &settings) noexcept(false) = 0;

        virtual void regenerate(const Settings &settings) noexcept(false) = 0;

        virtual void close() noexcept = 0;

    };

    class IRenderer {

    };
}
