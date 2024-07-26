#pragma once

#include "tensors.h"
#include "attributes.h"
#include "enums.h"

#include <optional>
#include <string>

namespace ZEN {
    /**
     * 3D vertex
     *
     * @ref vertices
     * @ref geometry-relationships
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

    class VertexAttrName {
    public:
        /**
         * Get the stringified name for an attribute.
         * This is useful in a few scenarios including Shader Builder translations.
         *
         * @param attr
         * @return
         */
        static std::string getAsString(VertexAttribute attr);
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

        /**
         * Retrieve the total size of attributes (contained in a list).
         *
         * @param attributes
         * @return
         */
        static uint8_t getSize(const std::vector<VertexAttribute> &attributes);
    };
}
