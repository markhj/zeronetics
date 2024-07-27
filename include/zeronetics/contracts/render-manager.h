
#pragma once

#include "cameras.h"
#include "renderable.h"
#include "shader.h"

#include "zeronetics/core/render-settings.h"

#include <memory>

namespace ZEN {
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

    class IRenderLayer {
    public:
        /**
         * Render settings, such as depth testing and primitive type
         * (point, line, triangle, etc.)
         */
        RenderSettings settings;

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
         * Retrieve unique ID for this layer.
         */
        [[nodiscard]] virtual unique_id getLayerId() noexcept = 0;

        /**
         * Retrieve list of attributes which make up each vertex.
         */
        [[nodiscard]] virtual std::vector<VertexAttribute> getAttributes() const noexcept = 0;
    };

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

        /**
         * The layer which holds authority over the request.
         */
        std::shared_ptr<IRenderLayer> renderLayer;
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
    class IRenderManager {
    public:
        std::vector<std::shared_ptr<IRenderLayer>> layers;

        /**
         * Reset the allocation details contained within all renderables
         * in the manager.
         */
        virtual void resetAllocations() const noexcept = 0;

        /**
         * Submit a request.
         *
         * @param request
         */
        virtual void request(const IRendererRequest &request) = 0;

        /**
         * Retrieve the list of requests.
         *
         * @return
         */
        virtual std::vector<std::shared_ptr<IRendererRequest>> getRequests() = 0;

        /**
         * Clear the list of requests.
         */
        virtual void clearRequests() = 0;

        /**
         * Iterate through pending requests and clear the list once handled.
         *
         * @note This is an alternative approach to using ``getRequests`` and
         *      ``clearRequests`` which leverages more handling to the processor.
         *
         * @param handle
         */
        virtual void forEachRequest(const std::function<void(const std::shared_ptr<IRendererRequest> &request)> &handle) = 0;
    };
}
