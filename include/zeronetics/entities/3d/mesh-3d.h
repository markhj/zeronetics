#pragma once

#include "zeronetics/core/tensors.h"
#include "zeronetics/core/vertices.h"
#include "zeronetics/entities/entity.h"
#include "zeronetics/contracts/renderable.h"

namespace ZEN {
    class Mesh3D : public Entity3D,
                   public IRenderable3D {
    public:
        [[nodiscard]] std::vector<Vertex3D> getVertices() const noexcept override;
    };
}
