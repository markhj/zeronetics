#pragma once

#include <vector>

#include "zeronetics/core/vertices.h"

namespace ZEN {
    /**
     * A description/request of the shader to be build by a Shader Builder.
     */
    struct ShaderBlueprint {
        std::vector<VertexAttribute> attributes;

        Projection projection = Projection::Orthographic;
    };
}
