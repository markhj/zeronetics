#include "zeronetics/core/vertices.h"
#include "zeronetics/logging/logging.h"

uint8_t ZEN::VertexAttrSize::getSize(ZEN::VertexAttribute attr) {
    switch (attr) {
        case VertexAttribute::Position2D:
        case VertexAttribute::TextureUV:
            return 2;
        case VertexAttribute::Position3D:
        case VertexAttribute::ColorRGB:
        case VertexAttribute::Normal3D:
        case VertexAttribute::Tangent3D:
        case VertexAttribute::BiTangent3D:
            return 3;
        case VertexAttribute::colorRGBA:
            return 4;
        default:
            ZEN_LIB_ERROR("Missing vertex attribute size m_mapping.");
            return 0;
    }
}
