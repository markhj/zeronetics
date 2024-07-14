#pragma once

#include "vertices.h"
#include "zeronetics/core/typedefs.h"

namespace ZEN {
    class AABB3D {
    public:
        gw_float x, y, z;

        AABB3D(gw_float width, gw_float height, gw_float depth);

        static AABB3D from(const std::vector<Vertex3D> &vertices);

        AABB3D &operator/(gw_float divider);

        explicit operator Vec3() const;

    };
}
