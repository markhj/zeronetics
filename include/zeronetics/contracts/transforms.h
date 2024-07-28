#pragma once

#include "zeronetics/core/tensors.h"

namespace ZEN {
    class IPosition3D {
    public:
        Vec3 position = Vec3(0.0);
    };

    class ITransforms3D : public IPosition3D {
    public:

    };
}
