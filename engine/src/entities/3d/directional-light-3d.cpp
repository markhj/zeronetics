#include "zeronetics/entities/3d/directional-light-3d.h"
#include <format>

void ZEN::DirectionalLight3D::setOnShader(const std::string &key,
                                          const std::shared_ptr<ZEN::IShader> &shader) {
    shader->set(std::format("{}.direction", key), direction);
    shader->set(std::format("{}.color", key), color);
}
