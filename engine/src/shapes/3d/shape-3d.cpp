#include <iostream>
#include <utility>

#include "zeronetics/core/shape.h"
#include "zeronetics/helpers/vertices.h"
#include "zeronetics/logging/logging.h"


ZEN::Shape3D::Shape3D(std::vector<Vertex3D> vertices) : m_generated(std::move(vertices)) {
}

std::vector<ZEN::Vertex3D> ZEN::Shape3D::getVertices() noexcept {
    if (m_generated.empty()) {
        m_generated = make();
    }

    // Calculate normals (if not provided)
    // We work from the assumption that if the first vertex doesn't
    // have a normal, then probably all of them are missing
    if (!m_generated[0].normal.has_value()) {
        ZEN_WARN("3D shape was not provided normals, attempting to auto-fill, but this may produce incorrect results.",
                 ZEN::LogCategory::VertexDataIntegrity);
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
    }

    return m_generated;
}

std::vector<ZEN::Vertex3D> ZEN::Shape3D::make() const noexcept {
    return m_generated;
}
