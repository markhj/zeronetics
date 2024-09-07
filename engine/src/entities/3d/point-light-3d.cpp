#include "zeronetics/entities/3d/point-light-3d.h"
#include <format>


void ZEN::PointLight3D::setOnShader(const std::string &key,
                                    const std::shared_ptr<ZEN::IShader> &shader) {
    shader->set(std::format("{}.position", key), position);
    shader->set(std::format("{}.color", key), color);
    shader->set(std::format("{}.constant", key), constant);
    shader->set(std::format("{}.linear", key), linear);
    shader->set(std::format("{}.quadratic", key), quadratic);
}

ZEN::EntityRegistration ZEN::PointLight3D::getRegistration() {
    return {
            .name = "Point Light 3D",
    };
}
