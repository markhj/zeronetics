#pragma once

#include <cstdint>

namespace ZEN {
    /**
     * Screen resolution with width and height.
     */
    struct ScreenResolution {
        uint16_t w, h;
    };

    /**
     * Hardware settings, including graphics and audio.
     */
    struct Settings {
        ScreenResolution screenResolution{1920, 1080};
    };
}
