#include "zeronetics/render/render-manager.h"

ZEN::unique_id ZEN::RenderLayer::getLayerId() noexcept {
    return getUniqueId();
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
