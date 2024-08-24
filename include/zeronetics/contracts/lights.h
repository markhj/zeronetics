#pragma once

#include <memory>

#include "shader.h"
#include "zeronetics/core/attributes.h"

namespace ZEN {
    /**
     * Light Contract
     *
     * @ref lights-tutorial
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
     * Directional Light Contract
     *
     * @ref lights-tutorial
     */
    template<typename T>
    class IDirectionalLight : public ILight {
    public:
        T direction;
    };

    /**
     * Point Light Contract
     *
     * @ref lights-tutorial
     */
    class IPointLight : public ILight {
    public:
        /**
         * Constant attenuation factor (minimal light falloff)
         */
        float constant = 1.0;

        /**
         * Linear attenuation factor (light diminishes linearly with distance)
         */
        float linear = 0.01;

        /**
         * Quadratic attenuation factor (light diminishes exponentially with distance)
         */
        float quadratic = 0.032;
    };
}
