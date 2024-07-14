#pragma once

#include "zeronetics/core/typedefs.h"
#include "zeronetics/core/vertices.h"
#include "zeronetics/core/shape.h"

namespace ZEN {
    class Cube : public Shape3D {
    public:
        Cube();

        explicit Cube(gw_float scalar);

        Cube(gw_float width, gw_float height, gw_float depth);

    protected:
        [[nodiscard]] std::vector<Vertex3D> make() const noexcept override;

    private:
        gw_float m_width, m_height, m_depth;

    };
}
