#pragma once

#include "zeronetics/core/enums.h"
#include "zeronetics/core/tensors.h"
#include <string>

namespace ZEN {
    /**
     * Shader contract
     */
    class IShader {
    public:
        /**
         * Create the program and register it on the GPU.
         */
        virtual void create() noexcept(false) = 0;

        /**
         * Set the source for a shader stage.
         *
         * @param shaderStage
         * @param source
         */
        virtual void setSource(ShaderStage shaderStage,
                               const std::string &source) noexcept = 0;

        /**
         * Compile the shader.
         * All sources must have been set prior to calling this step.
         */
        virtual void compile() noexcept(false) = 0;

        /**
         * Activate this particular shader.
         */
        virtual void use() noexcept = 0;

        /**
         * Set boolean value.
         * '
         * @param location
         * @param value
         */
        virtual void set(const std::string &location, bool value) noexcept = 0;

        /**
         * Set integer.
         *
         * @param location
         * @param value
         */
        virtual void set(const std::string &location, int value) noexcept = 0;

        /**
         * Set float.
         *
         * @param location
         * @param value
         */
        virtual void set(const std::string &location, float value) noexcept = 0;

        /**
         * Set 2-dimensional vector.
         *
         * @param location
         * @param value
         */
        virtual void set(const std::string &location, ZEN::Vec2 value) noexcept = 0;

        /**
         * Set 3-dimensional vector.
         *
         * @param location
         * @param value
         */
        virtual void set(const std::string &location, ZEN::Vec3 value) noexcept = 0;

        /**
         * Set 4-dimensional vector.
         *
         * @param location
         * @param value
         */
        virtual void set(const std::string &location, ZEN::Vec4 value) noexcept = 0;

        /**
         * Set Mat4x4 value on the shader.
         *
         * @param location
         * @param value
         */
        virtual void set(const std::string &location, ZEN::Mat4x4 value) noexcept = 0;
    };
}
