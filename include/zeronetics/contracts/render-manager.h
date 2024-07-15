
#pragma once

#include "cameras.h"
#include "renderable.h"
#include "shader.h"

#include <memory>

namespace ZEN {
    /**
     * Contract for renderer request
     *
     * @ref render-manager
     */
    struct IRendererRequest {
        /**
         * The type of request, e.g. allocation or de-allocation.
         */
        RenderManagerRequest request;

        /**
         * The target renderable.
         */
        std::shared_ptr<IRenderable3D> renderable3d;
    };

    /**
     * Render group
     *
     * @ref render-groups
     */
    struct IRenderGroup3D {
        /**
         * Shader with which the renderables of the group must be rendered.
         */
        std::shared_ptr<IShader> shader;

        /**
         * Unordered list of renderables.
         */
        std::unordered_map<std::string, std::shared_ptr<IRenderable3D>> renderables3d;
    };

    /**
     * A Render Manager is a way for "something" and a renderer
     * to communicate, without introducing coupling between that "something"
     * and the renderer. The "something" is typically some sort
     * of scene-related object, but it doesn't have to be.
     *
     * They have different authorities over the render manager, and can
     * both update its data. For instance, a scene-like object can
     * place requests, and the renderer can remove them, when they are
     * processed.
     *
     * @ref render-manager
     */
    struct IRenderManager {
        /**
         * The primary camera.
         */
        std::shared_ptr<ICamera3D> camera3d;

        /**
         * List of relevant groups.
         *
         * @ref render-groups
         */
        std::vector<std::shared_ptr<IRenderGroup3D>> renderGroups3d;

        /**
         * List of requests.
         */
        std::vector<std::unique_ptr<IRendererRequest>> requests;

        /**
         * Reset the allocation details contained within all renderables
         * in the manager.
         */
        virtual void resetAllocations() const noexcept = 0;

    };
}

