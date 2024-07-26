#pragma once

#include "zeronetics/core/shader-blueprint.h"
#include "zeronetics/render/render-manager.h"

namespace ZEN::Gizmos {
    class Grid3D {
    public:
        [[nodiscard]] ShaderBlueprint getShaderBlueprint() const noexcept;

        RenderLayer generate();

    private:
        uint16_t lines = 10;

        gw_float spacing = 1.0;

        ColorRGB lineColor = ColorRGB(1.0, 1.0, 1.0),
                 xAxisColor = ColorRGB(1.0, 0.0, 0.0),
                 yAxisColor = ColorRGB(0.0, 1.0, 0.0),
                 zAxisColor = ColorRGB(0.0, 0.0, 1.0);

        std::vector<VertexAttribute> m_attributes = {
                VertexAttribute::Position3D,
                VertexAttribute::ColorRGB,
        };
    };
}
