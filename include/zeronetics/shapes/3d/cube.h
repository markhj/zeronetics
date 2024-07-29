#pragma once

#include "zeronetics/core/typedefs.h"
#include "zeronetics/core/vertices.h"
#include "zeronetics/core/shape.h"

namespace ZEN {
    /**
     * Cube (3D)
     */
    class Cube : public Shape3D {
    public:
        /**
         * Create a cube of 1x1x1.
         */
        Cube();

        /**
         * Create a cube which has the same length on all sides.
         *
         * @param scalar
         */
        explicit Cube(gw_float scalar);

        /**
         * Create a cube with individual width, height and depth values.
         *
         * @param width
         * @param height
         * @param depth
         */
        Cube(gw_float width, gw_float height, gw_float depth);

    protected:
        [[nodiscard]] std::vector<Vertex3D> make() const noexcept override;

    private:
        gw_float m_width, m_height, m_depth;

    };
}
