#include "zeronetics/render/render-manager.h"

ZEN::RenderLayer::RenderLayer(const std::vector<ZEN::VertexAttribute> &attributes) : m_attributes(attributes) {

}


ZEN::unique_id ZEN::RenderLayer::getLayerId() noexcept {
    return getUniqueId();
}

std::vector<ZEN::VertexAttribute> ZEN::RenderLayer::getAttributes() const noexcept {
    return m_attributes;
}

void ZEN::RenderManager::resetAllocations() const noexcept {
    for (const auto &layer: layers) {
        for (const auto &group: layer->renderGroups3d) {
            for (auto &item: group->renderables3d) {
                item.second->gpuAlloc.reset();
            }
        }
    }
}
