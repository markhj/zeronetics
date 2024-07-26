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
    struct RenderManager : public IRenderManager {
        void resetAllocations() const noexcept override;
    };
}
