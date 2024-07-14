#pragma once

#include "zeronetics/entities/3d/camera-3d.h"
#include "zeronetics/contracts/render-manager.h"
#include <memory>

namespace ZEN {
    struct RendererRequest : public IRendererRequest {};

    struct RenderGroup3D : public IRenderGroup3D {

    };

    struct RenderManager : public IRenderManager {
        void resetAllocations() const noexcept override;
    };
}
