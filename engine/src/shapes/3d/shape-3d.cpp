#include "zeronetics/core/shape.h"

ZEN::Shape3D::Shape3D(const std::vector<Vertex3D> &vertices) : m_generated(vertices) {
}

std::vector<ZEN::Vertex3D> ZEN::Shape3D::getVertices() noexcept {
    if (m_generated.empty()) {
        m_generated = make();
    }
    return m_generated;
}
