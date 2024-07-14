#pragma once

#include "zeronetics/core/vertices.h"

#include <vector>

namespace ZEN {
    template<typename T>
    class IShape {
    public:
        /**
         * Return the vertices.
         *
         * A function typically implemented by a general Shape class, and not
         * by each individual shape.
         *
         * @return
         */
        [[nodiscard]] virtual std::vector<T> getVertices() noexcept = 0;

    protected:
        /**
         * Construct and return the shape vertices.
         *
         * @return
         */
        [[nodiscard]] virtual std::vector<T> make() const noexcept = 0;

    };

    class IShape3D : public IShape<Vertex3D> {
    public:


    };
}
