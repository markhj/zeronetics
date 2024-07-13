#pragma once

#include "zeronetics/core/gpu-alloc.h"

namespace ZEN {
    class IRenderable3D {
    public:
        [[nodiscard]] virtual std::vector<Vertex3D> getVertices() const noexcept = 0;
    };
}
