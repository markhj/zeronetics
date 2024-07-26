#pragma once

#include "zeronetics/core/typedefs.h"
#include "zeronetics/core/vertices.h"
#include <vector>

namespace ZEN {
    class Vertices {
    public:
        static std::vector<gw_float> flattenVertex3D(const Vertex3D &vertex,
                                                     const std::vector<VertexAttribute> &attributes);
    };
}
