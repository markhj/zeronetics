#pragma once

#include "asset-types.h"
#include "assets.h"
#include "zeronetics/contracts/render-manager.h"

namespace ZEN {
    /**
     * Renderer contract
     */
    class IRenderer {
    public:
        /**
         * Background color is visible where nothing is rendered in front.
         */
        ColorRGB backgroundColor = ColorRGB(0.0, 0.02, 0.1);

        /**
         * Optional configuration of the viewport's position and size.
         */
        virtual void setViewport(const Viewport &viewport) = 0;

        /**
         * Set the render manager which the renderer will communicate
         * with regarding allocations, de-allocations, updates, and more.
         *
         * @param renderManager
         */
        virtual void setRenderManager(const std::shared_ptr<IRenderManager> &renderManager) noexcept(false) = 0;

        /**
         * All steps to initialize the renderer.
         */
        virtual void initialize() = 0;

        /**
         * Returns true, if the renderer has been successfully initialized.
         *
         * @return
         */
        [[nodiscard]] virtual bool isInitialized() const noexcept = 0;

        /**
         * Clear buffers between rendering of frames, e.g. color,
         * stencil and depth buffers.
         */
        virtual void clear() noexcept = 0;

        /**
         * Render loop.
         */
        virtual void render() = 0;
    };
}
