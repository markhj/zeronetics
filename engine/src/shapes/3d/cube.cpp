#include "zeronetics/shapes/3d/cube.h"


ZEN::Cube::Cube() : m_width(1.0), m_height(1.0), m_depth(1.0) {
}

ZEN::Cube::Cube(gw_float scalar) : m_width(scalar), m_height(scalar), m_depth(scalar) {
}

ZEN::Cube::Cube(gw_float width, gw_float height, gw_float depth) : m_width(width),
                                                                   m_height(height),
                                                                   m_depth(depth) {
}

std::vector<ZEN::Vertex3D> ZEN::Cube::make() const noexcept {
    std::vector<Vertex3D> res;

    res.push_back({.position = {0.0, 0.0, 0.0}});
    res.push_back({.position = {m_width, 0.0, 0.0}});
    res.push_back({.position = {0.0, m_height, 0.0}});

    return res;
}
