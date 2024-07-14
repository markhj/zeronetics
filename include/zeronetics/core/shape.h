#pragma once

#include "zeronetics/contracts/shapes.h"

namespace ZEN {
    class Shape3D : public IShape3D {
    public:
        [[nodiscard]] std::vector<Vertex3D> getVertices() noexcept final;

    private:
        std::vector<Vertex3D> m_generated;
        
    };
}
