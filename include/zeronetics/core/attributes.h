#pragma once

#include "tensors.h"

namespace ZEN {
    class ColorRGB : public Vec3 {
    public:
        using Vec3::Vec3;

    };

    class ColorRGBA : public Vec4 {
    public:
        using Vec4::Vec4;

    };
}
