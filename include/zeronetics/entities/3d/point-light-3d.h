#pragma once

#include "zeronetics/contracts/lights.h"
#include "zeronetics/contracts/transforms.h"
#include "zeronetics/entities/entity.h"

namespace ZEN {
    /**
     * Point Light in 3D
     *
     * Point lights shine in all directions with limited distance.
     *
     * They have position, but not direction.
     *
     * @ref lights-tutorial
     */
    class PointLight3D : public IPointLight,
                         public IPosition3D,
                         public Entity3D {
    public:
        /**
         * Retrieve the entity registration.
         *
         * @return
         */
        EntityRegistration getRegistration() override;

        /**
         * Instruct the shader about the properties of this point light.
         *
         * @param key
         * @param shader
         */
        void setOnShader(const std::string &key,
                         const std::shared_ptr<ZEN::IShader> &shader) override;
    };
}
