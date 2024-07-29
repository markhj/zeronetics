#pragma once

#include "zeronetics/contracts/lights.h"
#include "zeronetics/contracts/transforms.h"

namespace ZEN {
    /**
     * Point Light in 3D
     *
     * Point lights shine in all directions with limited distance.
     *
     * They have position, but not direction.
     */
    class PointLight3D : public IPointLight,
                         public IPosition3D {
    public:
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
