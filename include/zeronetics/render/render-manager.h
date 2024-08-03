#pragma once

#include "zeronetics/contracts/render-manager.h"
#include "zeronetics/entities/3d/camera-3d.h"
#include "zeronetics/traits/has-unique-id.h"
#include <memory>

namespace ZEN {
    /**
     * Basic Renderer Request
     */
    struct RendererRequest : public IRendererRequest {};

    /**
     * 3D Render Group
     */
    struct RenderGroup3D : public IRenderGroup3D {};

    /**
     * Render Layer
     */
    class RenderLayer : public IRenderLayer,
                        public HasUniqueId {
    public:
        /**
         * Initialize a render layer with a specified list of vertex
         * attributes.
         *
         * @param attributes
         */
        explicit RenderLayer(const std::vector<VertexAttribute> &attributes);

        /**
         * The this layer's unique ID.
         *
         * @return
         */
        [[nodiscard]] unique_id getLayerId() noexcept override;

        /**
         * Get the vertex attributes assigned to this layer.
         *
         * @return
         */
        [[nodiscard]] std::vector<VertexAttribute> getAttributes() const noexcept override;

        /**
         * Create the layer content from a scene object.
         *
         * @param scene
         */
        void generateFrom(const std::shared_ptr<IScene> &scene) override;

    private:
        std::vector<VertexAttribute> m_attributes;
    };

    /**
     * Implementation of basic Render Manager.
     */
    class RenderManager : public IRenderManager {
    public:
        /**
         * Reset all existing allocations in all layers.
         */
        void resetAllocations() const noexcept override;

        /**
         * Make a reuqest.
         *
         * @param request
         */
        virtual void request(const IRendererRequest &request) override;

        /**
         * Retrieve all pending requests.
         * @return
         */
        virtual std::vector<std::shared_ptr<IRendererRequest>> getRequests() override;

        /**
         * Clear all pending requests.
         */
        void clearRequests() override;

        /**
         * Iterate through all requests, and clear them in the end.
         *
         * @param handle
         */
        void forEachRequest(const std::function<void(const std::shared_ptr<IRendererRequest> &request)> &handle) override;

        /**
         * Attach a render layer.
         *
         * @param layer
         */
        void attachLayer(const std::shared_ptr<IRenderLayer> &layer) override;

        /**
         * Allocate the renderables contained on a layer.
         *
         * @param layer
         */
        void allocateLayer(const std::shared_ptr<IRenderLayer> &layer) override;

        /**
         * Get the list of layers.
         *
         * @return
         */
        std::vector<std::shared_ptr<IRenderLayer>> getLayers() override;

    private:
        std::vector<std::shared_ptr<IRendererRequest>> m_requests;

        std::vector<std::shared_ptr<IRenderLayer>> m_layers;

    };
}
