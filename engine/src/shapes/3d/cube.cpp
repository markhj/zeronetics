#include "zeronetics/shapes/3d/cube.h"


ZEN::Cube::Cube() : m_width(1.0), m_height(1.0), m_depth(1.0) {
}

ZEN::Cube::Cube(gw_float scalar) : m_width(scalar), m_height(scalar), m_depth(scalar) {
}

ZEN::Cube::Cube(gw_float width, gw_float height, gw_float depth) : m_width(width),
                                                                   m_height(height),
                                                                   m_depth(depth) {
}

inline void createFace(std::vector<ZEN::Vertex3D> &res,
                       const ZEN::Vec3 &a,
                       const ZEN::Vec3 &b,
                       const ZEN::Vec3 &c,
                       const ZEN::Vec3 &d) {
    res.push_back({.position = a});
    res.push_back({.position = b});
    res.push_back({.position = c});
    res.push_back({.position = d});
    res.push_back({.position = c});
    res.push_back({.position = b});
}

std::vector<ZEN::Vertex3D> ZEN::Cube::make() const noexcept {
    std::vector<Vertex3D> res;

    gw_float x = m_width / 2.0f,
             y = m_height / 2.0f,
             z = m_depth / 2.0f;

    for (const gw_float i: {-1.0f, 1.0f}) {
        // Front and back
        createFace(res,
                   {-x, -y, i * z},
                   {x, -y, i * z},
                   {-x, y, i * z},
                   {x, y, i * z});

        // Sides
        createFace(res,
                   {i * x, -y, -z},
                   {i * x, y, -z},
                   {i * x, -y, z},
                   {i * x, y, z});

        // Top and bottom
        createFace(res,
                   {-x, i * y, -z},
                   {x, i * y, -z},
                   {-x, i * y, z},
                   {x, i * y, z});
    }

    return res;
}