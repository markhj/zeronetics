#pragma once

#include "zeronetics/core/attributes.h"

namespace ZEN {
    struct ILight {
        ColorRGB color = ColorRGB(1.0, 1.0, 1.0);
    };

    struct IPointLight : public ILight {
        float constant = 1.0,
              linear = 0.01,
              quadratic = 0.032;
    };
}
