#pragma once

#include <memory>

#include "shader.h"
#include "zeronetics/core/attributes.h"

namespace ZEN {
    /**
     * Light Contract
     */
    class ILight {
    public:
        /**
         * Light color.
         */
        ColorRGB color = ColorRGB(1.0, 1.0, 1.0);

        /**
         * Store information about the light on the shader.
         *
         * @param key
         * @param shader
         */
        virtual void setOnShader(const std::string &key,
                                 const std::shared_ptr<ZEN::IShader> &shader) = 0;
    };

    /**
     * Point Light Contract
     */
    class IPointLight : public ILight {
    public:
        float constant = 1.0,
              linear = 0.01,
              quadratic = 0.032;
    };
}
