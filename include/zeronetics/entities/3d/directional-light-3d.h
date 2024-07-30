#pragma once

#include "zeronetics/contracts/lights.h"

namespace ZEN {
    /**
     * Directional Light for 3D Scene
     */
    class DirectionalLight3D : public IDirectionalLight<Vec3> {
    public:
        /**
         * The direction of the light.
         */
        Vec3 direction = Vec3(0.0, -1.0, 0.0);

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
