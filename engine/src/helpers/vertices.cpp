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
