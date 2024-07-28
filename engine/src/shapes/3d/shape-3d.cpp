#include <iostream>
#include <utility>

#include "zeronetics/core/shape.h"
#include "zeronetics/helpers/vertices.h"


ZEN::Shape3D::Shape3D(std::vector<Vertex3D> vertices) : m_generated(std::move(vertices)) {
}

std::vector<ZEN::Vertex3D> ZEN::Shape3D::getVertices() noexcept {
    if (m_generated.empty()) {
        m_generated = make();
    }

    // Calculate normals
    std::vector<Vertex3D *> pairs;
    for (Vertex3D &vertex: m_generated) {
        pairs.emplace_back(&vertex);
        if (pairs.size() == 3) {
            Vec3 normal = Vertices::calculateNormal(pairs[0]->position,
                                                      pairs[1]->position,
                                                      pairs[2]->position);
            pairs[0]->normal = pairs[1]->normal = pairs[2]->normal = normal;
            pairs.clear();
        }
    }

    return m_generated;
}

std::vector<ZEN::Vertex3D> ZEN::Shape3D::make() const noexcept {
    return m_generated;
}
