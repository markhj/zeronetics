/**
 * Tensors - Vectors and matrices
 *
 * @ref tensors
 */

#pragma once

#include <glm/glm.hpp>

namespace ZEN {
    /**
     * 2-dimensional vector.
     */
    using Vec2 = glm::vec2;

    /**
     * 3-dimensional vector.
     */
    using Vec3 = glm::vec3;

    /**
     * 4-dimensional vector.
     */
    using Vec4 = glm::vec4;

    /**
     * 4x4 matrix.
     */
    using Mat4x4 = glm::mat4x4;

    /**
     * Model-View-Projection container.
     */
    struct MVP {
        Mat4x4 model, view, projection;
    };
}
