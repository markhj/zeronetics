#pragma once

#include "zeronetics/contracts/lights.h"
#include "zeronetics/entities/entity.h"

namespace ZEN {
    /**
     * Directional Light for 3D Scene
     *
     * @ref lights-tutorial
     */
    class DirectionalLight3D : public IDirectionalLight<Vec3>,
                               public Entity3D {
    public:
        /**
         * The direction of the light.
         */
        Vec3 direction = Vec3(0.0, -1.0, 0.0);

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
