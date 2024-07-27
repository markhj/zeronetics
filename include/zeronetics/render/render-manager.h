#pragma once

#include "zeronetics/contracts/render-manager.h"
#include "zeronetics/entities/3d/camera-3d.h"
#include "zeronetics/traits/has-unique-id.h"
#include <memory>

namespace ZEN {
    /**
     *
     */
    struct RendererRequest : public IRendererRequest {};

    /**
     *
     */
    struct RenderGroup3D : public IRenderGroup3D {
    };

    /**
     *
     */
    class RenderLayer : public IRenderLayer,
                        public HasUniqueId {
    public:
        explicit RenderLayer(const std::vector<VertexAttribute> &attributes);

        [[nodiscard]] unique_id getLayerId() noexcept override;

        [[nodiscard]] std::vector<VertexAttribute> getAttributes() const noexcept override;

    private:
        std::vector<VertexAttribute> m_attributes;
    };

    /**
     *
     */
    class RenderManager : public IRenderManager {
    public:
        void resetAllocations() const noexcept override;

        virtual void request(const IRendererRequest &request) override {
            m_requests.push_back(std::make_shared<RendererRequest>(request));
        };

        virtual std::vector<std::shared_ptr<IRendererRequest>> getRequests() override {
            return m_requests;
        };

        void clearRequests() override {
            m_requests.clear();
        }

        void forEachRequest(const std::function<void(const std::shared_ptr<IRendererRequest> &request)> &handle) override {
            std::for_each(m_requests.begin(),
                          m_requests.end(),
                          [&](const std::shared_ptr<IRendererRequest> &item) {
                                handle(item);
                          });

            clearRequests();
        }

    private:
        std::vector<std::shared_ptr<IRendererRequest>> m_requests;
    };
}
