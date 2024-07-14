#pragma once

#include "zeronetics/core/tensors.h"
#include "zeronetics/core/vertices.h"
#include "zeronetics/core/shape.h"
#include "zeronetics/entities/entity.h"
#include "zeronetics/contracts/renderable.h"

#include <memory>

namespace ZEN {
    class Mesh3D : public Entity3D,
                   public IRenderable3D {
    public:
        explicit Mesh3D(const std::vector<Vertex3D> &vertices);

        explicit Mesh3D(const std::shared_ptr<IShape3D> &shape);

        [[nodiscard]] std::vector<Vertex3D> getVertices() const noexcept override;

    private:
        std::shared_ptr<IShape3D> m_shape;

        std::vector<Vertex3D> m_customVertices;

    };
}
