#pragma once

#include "tensors.h"

namespace ZEN {
    /**
     * RGB Color
     *
     * Based on the 3-dimensional vector where:
     *
     * x = Red (r)
     * y = Green (g)
     * z = Blue (b)
     */
    class ColorRGB : public Vec3 {
    public:
        using Vec3::Vec3;
    };

    /**
     * RGB Color with Alpha channel
     *
     * Based on 4-dimensional vector.
     *
     * Works similar to ZEN::ColorRGB, but with the addition
     * of the alpha channel (``a``) which can be used to control
     * transparency.
     */
    class ColorRGBA : public Vec4 {
    public:
        using Vec4::Vec4;
    };
}
