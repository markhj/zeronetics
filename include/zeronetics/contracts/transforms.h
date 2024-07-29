#pragma once

#include "zeronetics/core/tensors.h"

namespace ZEN {
    /**
     * Any object that has a position in 3D space should
     * inherit this class.
     */
    class IPosition3D {
    public:
        /**
         * Position in 3D space.
         */
        Vec3 position = Vec3(0.0);
    };

    /**
     * Any object that has all common 3D transforms can
     * inherit this class instead of the individual transforms.
     */
    class ITransforms3D : public IPosition3D {
    public:

    };
}
