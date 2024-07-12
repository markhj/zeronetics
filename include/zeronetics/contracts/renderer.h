#pragma once

#include "zeronetics/contracts/render-manager.h"

namespace ZEN {
    /**
     * Renderer contract
     */
    class IRenderer {
    public:
        std::shared_ptr<IRenderManager> renderManager;

        virtual void initialize() = 0;

        [[nodiscard]] virtual bool isInitialized() const noexcept = 0;

        virtual void clear() noexcept = 0;

        virtual void render() = 0;

    };
}
