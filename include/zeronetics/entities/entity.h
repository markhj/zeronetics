#pragma once

#include "zeronetics/core/tensors.h"

namespace ZEN {
    class Entity {

    };

    class Entity3D : public Entity {
    public:
        Vec3 position = Vec3(1.0);
    };
}
