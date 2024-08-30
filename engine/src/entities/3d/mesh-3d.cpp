#include "zeronetics/entities/3d/mesh-3d.h"
#include "zeronetics/core/aabb.h"

std::vector<ZEN::Vertex3D> ZEN::Mesh3D::getVertices() const noexcept {
    auto vertices = m_shape ? m_shape->getVertices() : m_customVertices;

    for (auto &vertex: vertices) {
        vertex.position += position;
    }

    return vertices;
}

ZEN::Mesh3D::Mesh3D(const std::shared_ptr<IShape3D> &shape) {
    m_shape = shape;
}

ZEN::Mesh3D::Mesh3D(const std::vector<Vertex3D> &vertices) : m_customVertices(vertices) {
}

ZEN::EntityRegistration ZEN::Mesh3D::getRegistration() {
    return {
            .name = "3D Mesh",
    };
}
