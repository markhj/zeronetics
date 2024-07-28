#pragma once

#include "zeronetics/core/typedefs.h"
#include "zeronetics/core/vertices.h"
#include <vector>

namespace ZEN {
    class Vertices {
    public:
        static std::vector<gw_float> flattenVertex3D(const Vertex3D &vertex,
                                                     const std::vector<VertexAttribute> &attributes);

        /**
         * Calculate the normal from three given vectors.
         *
         * The vectors must be given in counter-clockwise order.
         *
         * @param a
         * @param b
         * @param c
         * @return
         */
        static Vec3 calculateNormal(const Vec3 &a, const Vec3 &b, const Vec3 &c) noexcept;
    };
}
