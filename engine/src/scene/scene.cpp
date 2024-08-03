#include "zeronetics/scene/scene.h"

void ZEN::Scene::add(const std::shared_ptr<IRenderable3D> &renderable) noexcept {
    m_renderables3d.emplace_back(renderable);
}

std::vector<std::shared_ptr<ZEN::IRenderable3D>> ZEN::Scene::getRenderable3Ds() const noexcept {
    return m_renderables3d;
}
