#include "zeronetics/core/shape.h"


std::vector<ZEN::Vertex3D> ZEN::Shape3D::getVertices() noexcept {
    if (m_generated.empty()) {
        m_generated = make();
    }
    return m_generated;
}
