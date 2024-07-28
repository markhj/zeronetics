#pragma once

#include "zeronetics/contracts/lights.h"
#include "zeronetics/contracts/transforms.h"
#include "zeronetics/core/tensors.h"

namespace ZEN {
    struct PointLight3D : public IPointLight,
                          public IPosition3D {
    };
}
