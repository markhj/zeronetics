#pragma once

#include <cstdint>

namespace ZEN {
    /**
     * Screen resolution with width and height.
     */
    struct ScreenResolution {
        /**
         * Screen width in pixels.
         */
        uint16_t w;

        /**
         * Screen height in pixels.
         */
        uint16_t h;
    };

    /**
     * Hardware settings, including graphics and audio.
     */
    struct Settings {
        /**
         * Monitor/screen resolution.
         */
        ScreenResolution screenResolution{1920, 1080};
    };
}
