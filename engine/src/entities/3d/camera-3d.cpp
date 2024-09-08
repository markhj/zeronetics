#include "zeronetics/entities/3d/camera-3d.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include <format>

ZEN::MVP ZEN::Camera3D::getModelViewProjection() const noexcept {
    auto projection = glm::perspective(fieldOfView,
                                       aspectRatio,
                                       clippingPlane[0],
                                       clippingPlane[1]);

    return {glm::mat4(1.0f),
            glm::lookAt(position, target, up),
            projection};
}

void ZEN::Camera3D::setOnShader(const std::string &key,
                                const std::shared_ptr<IShader> &shader) {
    shader->set(std::format("{}.position", key), position);
}

ZEN::EntityRegistration ZEN::Camera3D::getRegistration() {
    return {
            .typeName = "Camera3D",
            .name = "Camera 3D",
    };
}
