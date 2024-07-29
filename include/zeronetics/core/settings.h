#pragma once

#include "zeronetics/core/enums.h"
#include <cstdint>

namespace ZEN {
    /**
     * Screen resolution with width and height.
     */
    struct ScreenResolution : public ViewportSize {};

    /**
     * Hardware settings, including graphics and audio.
     *
     * @ref settings
     */
    struct Settings {
        /**
         * Monitor/screen resolution.
         */
        ScreenResolution screenResolution{960, 540};

        /**
         * Anti-alias.
         */
        AntiAlias antiAlias = AntiAlias::MSAA4X;

        /**
         * Vertical sync. (V-Sync)
         */
        bool vSync = true;
    };
}
