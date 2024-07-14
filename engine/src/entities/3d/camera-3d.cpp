#include "zeronetics/entities/3d/camera-3d.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

ZEN::MVP ZEN::Camera3D::getModelViewProjection() const noexcept {
    auto projection = glm::perspective(fieldOfView,
                                       aspectRatio,
                                       clippingPlane[0],
                                       clippingPlane[1]);

    return {glm::mat4(1.0f),
            glm::lookAt(position, target, up),
            projection};
}
