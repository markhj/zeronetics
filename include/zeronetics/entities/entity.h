#pragma once

#include "zeronetics/core/tensors.h"

namespace ZEN {
    /**
     * Base entity class.
     *
     * @ref entity-system
     */
    class Entity {
    };

    /**
     * 3D entity
     *
     * @note Whether a 3D entity has 3D transform properties (position,
     *      scale, rotation, etc.) is up to child classes to determine.
     *      Keep in mind that ZEN::ITransforms3D is also provided by
     *      ZEN::IRenderable3D.
     *
     * @ref entity-system
     */
    class Entity3D : public Entity {

    };
}
