#pragma once

#include "tensors.h"
#include "attributes.h"
#include "enums.h"

#include <optional>

namespace ZEN {
    struct Vertex3D {
        Vec3 position;
        std::optional<ColorRGB> color;
    };

    class VertexAttrSize {
    public:
        static uint8_t getSize(VertexAttribute attr);
    };
}
