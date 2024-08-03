#pragma once

#include "vertices.h"
#include "zeronetics/core/typedefs.h"

namespace ZEN {
    /**
     * Axis-Aligned Bounding Box 3D
     */
    class AABB3D {
    public:
        /**
         * Width (Size on X-axis)
         */
        gw_float x;

        /**
         * Height (Size on Y-axis)
         */
        gw_float y;

        /**
         * Depth (Size on Z-axis)
         */
        gw_float z;

        /**
         * Generate AABB3D from width, height and depth.
         *
         * @param width
         * @param height
         * @param depth
         */
        AABB3D(gw_float width, gw_float height, gw_float depth);

        /**
         * Calculate the bounding box from a set of vertices, and
         * return the AABB3D instance.
         *
         * @param vertices
         * @return
         */
        static AABB3D from(const std::vector<Vertex3D> &vertices);

        /**
         * Divide the size of the bounding box.
         *
         * @param divider
         * @return
         */
        AABB3D &operator/(gw_float divider);

        /**
         * Explicit conversion to ZEN::Vec3 (3-dimensional vector).
         *
         * @return
         */
        explicit operator Vec3() const;

    };
}
