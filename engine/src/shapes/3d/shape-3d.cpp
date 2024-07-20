#include <utility>

#include "zeronetics/core/shape.h"


std::vector<ZEN::Vertex3D> ZEN::Shape3D::getVertices() noexcept {
    if (m_generated.empty()) {
        m_generated = make();
    }
    return m_generated;
}

ZEN::Shape3D::Shape3D(std::vector<Vertex3D> vertices) : m_generated(std::move(vertices)) {
}
