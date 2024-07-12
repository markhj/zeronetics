#include "zeronetics/entities/3d/camera-3d.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

ZEN::MVP ZEN::Camera3D::getModelViewProjection() const noexcept {
    float aspectRatio = 800.0f / 600.0f;
    float fovY = glm::radians(45.0f);
    float nearClip = 0.1f;
    float farClip = 100.0f;
    auto projection = glm::perspective(fovY, aspectRatio, nearClip, farClip);

    return {glm::mat4(1.0f), glm::lookAt(position, target, up), projection};
}
