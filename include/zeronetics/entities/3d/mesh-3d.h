#pragma once

#include "zeronetics/core/tensors.h"
#include "zeronetics/core/vertices.h"
#include "zeronetics/core/shape.h"
#include "zeronetics/entities/entity.h"
#include "zeronetics/contracts/renderable.h"

#include <memory>

namespace ZEN {
    /**
     * 3D Mesh Entity
     *
     * @ref shapes
     * @ref geometry-relationships
     */
    class Mesh3D : public Entity3D,
                   public IRenderable3D {
    public:
        /**
         * Generate 3D mesh from list of vertices.
         *
         * @param vertices
         */
        explicit Mesh3D(const std::vector<Vertex3D> &vertices);

        /**
         * Generate 3D mesh from shape.
         *
         * @param shape
         */
        explicit Mesh3D(const std::shared_ptr<IShape3D> &shape);

        /**
         * Retrieve the vertices for the mesh.
         * @return
         */
        [[nodiscard]] std::vector<Vertex3D> getVertices() const noexcept override;

    private:
        /**
         * Shape that forms the mesh.
         *
         * @note Can be null if mesh is generated from custom list of vertices.
         */
        std::shared_ptr<IShape3D> m_shape;

        /**
         * Custom list of vertices.
         *
         * @note Can be empty, if mesh is generated from shape.
         */
        std::vector<Vertex3D> m_customVertices;

    };
}
