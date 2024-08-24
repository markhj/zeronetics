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
        /**
         * The Model matrix transforms local object coordinates.
         */
        Mat4x4 model;

        /**
         * The View matrix transforms world coordinates into camera (view) coordinates,
         * effectively positioning and orienting the camera within the scene.
         * This matrix represents the camera's position and orientation.
         */
        Mat4x4 view;

        /**
         * The Projection matrix transforms camera coordinates into clip space, handling
         * the perspective division (for perspective projection) or maintaining
         * parallel lines (for orthographic projection).
         * It defines the frustum and how the 3D scene is projected onto a 2D surface.
         */
        Mat4x4 projection;
    };
}
