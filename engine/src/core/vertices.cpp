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
            ZEN_LIB_ERROR("Missing vertex attribute size mapping.");
            return 0;
    }
}

std::string ZEN::VertexAttrName::getAsString(ZEN::VertexAttribute attr) {
    switch (attr) {
        case VertexAttribute::Position2D:
        case VertexAttribute::Position3D:
            return "Position";
        case VertexAttribute::ColorRGB:
        case VertexAttribute::colorRGBA:
            return "Color";
        case VertexAttribute::Normal3D:
            return "Normal";
        case VertexAttribute::Tangent3D:
            return "Tangent";
        case VertexAttribute::BiTangent3D:
            return "BiTangent";
        case VertexAttribute::TextureUV:
            return "TextureUV";
        default:
            ZEN_LIB_ERROR("Missing vertex attribute string mapping.");
            return "";
    }
}
