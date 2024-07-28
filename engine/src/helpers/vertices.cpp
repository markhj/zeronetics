#include "zeronetics/helpers/vertices.h"
#include "zeronetics/logging/logging.h"

std::vector<ZEN::gw_float> ZEN::Vertices::flattenVertex3D(const ZEN::Vertex3D &vertex,
                                                          const std::vector<VertexAttribute> &attributes) {

    std::vector<gw_float> result;

    for (const VertexAttribute &attr: attributes) {
        switch (attr) {
            case VertexAttribute::Position3D:
                result.emplace_back(vertex.position.x);
                result.emplace_back(vertex.position.y);
                result.emplace_back(vertex.position.z);
                break;
            case VertexAttribute::Normal3D:
                if (vertex.normal.has_value()) {
                    result.emplace_back(vertex.normal.value().x);
                    result.emplace_back(vertex.normal.value().y);
                    result.emplace_back(vertex.normal.value().z);
                } else {
                    ZEN_WARN("A vertex is missing normal.", ZEN::LogCategory::VertexDataIntegrity);
                    result.emplace_back(0.0);
                    result.emplace_back(0.0);
                    result.emplace_back(0.0);
                }
                break;
            case VertexAttribute::ColorRGB:
                if (vertex.color.has_value()) {
                    result.emplace_back(vertex.color->r);
                    result.emplace_back(vertex.color->g);
                    result.emplace_back(vertex.color->b);
                } else {
                    result.emplace_back(1.0);
                    result.emplace_back(1.0);
                    result.emplace_back(1.0);
                }
                break;
            default:
                ZEN_LIB_ERROR("Unmapped property in flattenVertex3D.");
        }
    }

    return result;
}

ZEN::Vec3 ZEN::Vertices::calculateNormal(const ZEN::Vec3 &a, const ZEN::Vec3 &b, const ZEN::Vec3 &c) noexcept {
    return Vec3(0.0, 1.0, 0.0);
    glm::vec3 ab = b - a;
    glm::vec3 ac = c - a;
    glm::vec3 normal = glm::cross(ab, ac);
    return glm::normalize(normal);
}
