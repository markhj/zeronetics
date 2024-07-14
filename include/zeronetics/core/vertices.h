#pragma once

#include "tensors.h"
#include "attributes.h"
#include "enums.h"

#include <optional>

namespace ZEN {
    /**
     * 3D vertex
     *
     * @ref vertices
     */
    struct Vertex3D {
        /**
         * Position
         */
        Vec3 position;

        /**
         * Color (RGB)
         */
        std::optional<ColorRGB> color;
    };

    /**
     * Vertex attribute size
     *
     * @ref vertices
     */
    class VertexAttrSize {
    public:
        /**
         * Retrieve the number of floating-point values
         * required to define the vertex attribute.
         *
         * @param attr
         * @return
         */
        static uint8_t getSize(VertexAttribute attr);
    };
}
