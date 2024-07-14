#include "zeronetics/core/aabb.h"
#include <map>


ZEN::AABB3D::AABB3D(gw_float width, gw_float height, gw_float depth) : x(width),
                                                                       y(height),
                                                                       z(depth) {
}

ZEN::AABB3D ZEN::AABB3D::from(const std::vector<Vertex3D> &vertices) {
    struct MinMax {
        gw_float min = 0.0, max = 0.0;
    };

    std::map<const char, MinMax> bounds = {{'x', {}},
                                           {'y', {}},
                                           {'z', {}}};

    for (const auto &v: vertices) {
        // Note: Code-style allowed to be broken in the following

        auto p = v.position;
        if (p.x < bounds['x'].min) bounds['x'].min = p.x;
        if (p.x > bounds['x'].max) bounds['x'].max = p.x;
        if (p.y < bounds['y'].min) bounds['y'].min = p.y;
        if (p.y > bounds['y'].max) bounds['y'].max = p.y;
        if (p.z < bounds['z'].min) bounds['z'].min = p.z;
        if (p.z > bounds['z'].max) bounds['z'].max = p.z;
    }

    return {
            bounds['x'].max - bounds['x'].min,
            bounds['y'].max - bounds['y'].min,
            bounds['z'].max - bounds['z'].min,
    };
}

ZEN::AABB3D &ZEN::AABB3D::operator/(ZEN::gw_float divider) {
    x /= divider;
    y /= divider;
    z /= divider;
    return *this;
}

ZEN::AABB3D::operator Vec3() const {
    return {x, y, z};
}
