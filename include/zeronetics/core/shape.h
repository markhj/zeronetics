#pragma once

#include "zeronetics/contracts/shapes.h"

namespace ZEN {
    /**
     * 3D shape
     *
     * @ref shapes
     * @ref geometry-relationships
     * @ref custom-shape-vertices
     * @ref custom-shape-class
     */
    class Shape3D : public IShape3D {
    public:
        Shape3D() = default;

        /**
         * Construct a shape from a set of custom vertices.
         *
         * @param vertices
         */
        explicit Shape3D(std::vector<Vertex3D> vertices);

        /**
         * Retrieve vertices that make up the shape.
         *
         * @note Once generated, the result will be stored in cache
         *      to make additional requests faster.
         *
         * @return
         */
        [[nodiscard]] std::vector<Vertex3D> getVertices() noexcept final;

    protected:
        [[nodiscard]] std::vector<Vertex3D> make() const noexcept override;

    private:
        /**
         * Caching of vertices.
         */
        std::vector<Vertex3D> m_generated;
        
    };
}
