#pragma once

#include "transforms.h"
#include "zeronetics/core/gpu-alloc.h"
#include "zeronetics/core/vertices.h"

namespace ZEN {
    class IRenderable3D : public ITransforms3D {
    public:
        [[nodiscard]] virtual std::vector<Vertex3D> getVertices() const noexcept = 0;
    };
}
