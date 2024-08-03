#include "zeronetics/render/render-manager.h"
#include <iostream>

ZEN::RenderLayer::RenderLayer(const std::vector<ZEN::VertexAttribute> &attributes) : m_attributes(attributes) {

}


ZEN::unique_id ZEN::RenderLayer::getLayerId() noexcept {
    return getUniqueId();
}

std::vector<ZEN::VertexAttribute> ZEN::RenderLayer::getAttributes() const noexcept {
    return m_attributes;
}

void ZEN::RenderLayer::generateFrom(const std::shared_ptr<IScene> &scene) {
    int i = 0;
    for (const auto &item: scene->getRenderable3Ds()) {
        ++i;

        // @todo: Replace with name from HXL file:
        renderGroups3d[0]->renderables3d["Obj" + std::to_string(i)] = item;
    }
}

void ZEN::RenderManager::resetAllocations() const noexcept {
    for (const auto &layer: m_layers) {
        for (const auto &group: layer->renderGroups3d) {
            for (auto &item: group->renderables3d) {
                item.second->gpuAlloc.reset();
            }
        }
    }
}

void ZEN::RenderManager::request(const ZEN::IRendererRequest &request) {
    m_requests.push_back(std::make_shared<RendererRequest>(request));
}

std::vector<std::shared_ptr<ZEN::IRendererRequest>> ZEN::RenderManager::getRequests() {
    return m_requests;
}

void ZEN::RenderManager::clearRequests() {
    m_requests.clear();
}

void ZEN::RenderManager::forEachRequest(const std::function<void(const std::shared_ptr<IRendererRequest> &)> &handle) {
    std::for_each(m_requests.begin(),
                  m_requests.end(),
                  [&](const std::shared_ptr<IRendererRequest> &item) {
                      handle(item);
                  });

    clearRequests();
}

void ZEN::RenderManager::attachLayer(const std::shared_ptr<IRenderLayer> &layer) {
    m_layers.push_back(layer);
}

std::vector<std::shared_ptr<ZEN::IRenderLayer>> ZEN::RenderManager::getLayers() {
    return m_layers;
}

void ZEN::RenderManager::allocateLayer(const std::shared_ptr<IRenderLayer> &layer) {
    for (auto &item: layer->renderGroups3d) {
        for (auto &renderable: item->renderables3d) {
            request({
                    .request = RenderManagerRequest::Allocate,
                    .renderable3d = renderable.second,
                    .renderLayer = layer,
            });
        }
    }
}
