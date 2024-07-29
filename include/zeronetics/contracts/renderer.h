#pragma once

#include "zeronetics/contracts/render-manager.h"

namespace ZEN {
    /**
     * Renderer contract
     */
    class IRenderer {
    public:
        ColorRGB backgroundColor = ColorRGB(0.0, 0.02, 0.1);

        virtual void setRenderManager(const std::shared_ptr<IRenderManager> &renderManager) noexcept(false) = 0;

        virtual void initialize() = 0;

        [[nodiscard]] virtual bool isInitialized() const noexcept = 0;

        virtual void clear() noexcept = 0;

        virtual void render() = 0;

    };
}
