#pragma once

#include <vector>

#include "zeronetics/core/vertices.h"

namespace ZEN {
    /**
     * Group light support.
     * You specify the number of slots per light-type.
     */
    struct LightSupport {
        /**
         * Number of 3D Point Lights.
         */
        uint16_t slotsPointLight3D = 0;
    };

    /**
     * A description/request of the shader to be build by a Shader Builder.
     */
    struct ShaderBlueprint {
        /**
         * List of vertex attributes which will be baked into the
         * source codes for the shader stages.
         */
        std::vector<VertexAttribute> attributes;

        /**
         * Code will be changed by the shader builder to respect
         * the projection.
         */
        Projection projection = Projection::Orthographic;

        /**
         * Light support, for instance how many slots must be
         * available for various types of lights.
         */
        LightSupport lightSupport;
    };
}
