#include "zeronetics/entities/3d/mesh-3d.h"
#include "zeronetics/core/aabb.h"

std::vector<ZEN::Vertex3D> ZEN::Mesh3D::getVertices() const noexcept {
    auto vertices = m_shape ? m_shape->getVertices() : m_customVertices;

    // @todo: Global space should be controlled by Scene, once implemented
    AABB3D aabb3d = AABB3D::from(vertices);
    Vec3 center = static_cast<Vec3>(aabb3d / 2.0);
    for (auto &vertex: vertices) {
        vertex.position += position - center;
    }

    return vertices;
}

ZEN::Mesh3D::Mesh3D(const std::shared_ptr<IShape3D> &shape) {
    m_shape = shape;
}

ZEN::Mesh3D::Mesh3D(const std::vector<Vertex3D> &vertices) : m_customVertices(vertices) {
}
