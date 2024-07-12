#pragma once

#include "zeronetics/core/tensors.h"
#include "zeronetics/entities/entity.h"
#include "zeronetics/contracts/cameras.h"

namespace ZEN {
    class Camera3D : public Entity3D,
                     public ICamera3D {
    public:
        [[nodiscard]] MVP getModelViewProjection() const noexcept override;
    };
}
