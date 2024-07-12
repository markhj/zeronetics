#pragma once

#include "zeronetics/core/tensors.h"

namespace ZEN {
    class ICamera3D {
    public:
        Vec3 target = Vec3(0.0);
        Vec3 up = Vec3(0.0, 1.0, 0.0);

        [[nodiscard]] virtual MVP getModelViewProjection() const noexcept = 0;

    };
}
