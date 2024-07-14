/**
 * Tensors - Vectors and matrices
 *
 * @ref tensors
 */

#pragma once

#include <glm/glm.hpp>

namespace ZEN {
    using Vec2 = glm::vec2;
    using Vec3 = glm::vec3;
    using Vec4 = glm::vec4;
    using Mat4x4 = glm::mat4x4;

    /**
     * Model-View-Projection container.
     */
    struct MVP {
        Mat4x4 model, view, projection;
    };
}
