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
        [[nodiscard]] unique_id getLayerId() noexcept override;
    };

    /**
     *
     */
    struct RenderManager : public IRenderManager {
        void resetAllocations() const noexcept override;
    };
}
