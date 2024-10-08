#pragma once

#include "transforms.h"
#include "zeronetics/core/gpu-alloc.h"
#include "zeronetics/core/vertices.h"

namespace ZEN {
    class IRenderable {
    public:
        /**
         * A special-purpose property which renderers
         * have authority over, and can choose to utilize
         * to store information about how they have allocated
         * the renderable.
         */
        std::optional<GPUAllocation> gpuAlloc;
    };

    /**
     * Contract for 3D Renderable
     */
    class IRenderable3D : public IRenderable,
                          public ITransforms3D {
    public:
        /**
         * Get the vertices which make up the renderable.
         *
         * @return
         */
        [[nodiscard]] virtual std::vector<Vertex3D> getVertices() const noexcept = 0;
    };
}
