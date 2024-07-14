#pragma once

#include "zeronetics/core/tensors.h"

namespace ZEN {
    class Entity {
    };

    /**
     *
     * @note Whether a 3D entity has 3D transform properties (position,
     *      scale, rotation, etc.) is up to child classes to determine.
     *      Keep in mind that ZEN::ITransforms3D is also provided by
     *      ZEN::IRenderable3D.
     */
    class Entity3D : public Entity {

    };
}
