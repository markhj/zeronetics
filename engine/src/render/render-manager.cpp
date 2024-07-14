#include "zeronetics/render/render-manager.h"


void ZEN::RenderManager::resetAllocations() const noexcept {
    for (const auto &group: renderGroups3d) {
        for (auto &item: group->renderables3d) {
            item.second->gpuAlloc.reset();
        }
    }
}
