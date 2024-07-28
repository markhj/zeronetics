#pragma once

#include <vector>

#include "zeronetics/core/vertices.h"

namespace ZEN {
    struct LightSupport {
        uint16_t slotsPointLight3D = 0;
    };

    /**
     * A description/request of the shader to be build by a Shader Builder.
     */
    struct ShaderBlueprint {
        std::vector<VertexAttribute> attributes;

        Projection projection = Projection::Orthographic;

        LightSupport lightSupport;
    };
}
