#pragma once

#include "zeronetics/contracts/shader.h"
#include "zeronetics/core/shader-blueprint.h"

#include <optional>

namespace ZEN {
    /**
     * A Shader Builder is a way to build simple shaders without writing code.
     * It serves a number of purposes from increasing usability to enabling
     * decoupling between components -- in other words, letting modules and
     * system components define wishes for their shading without needing to
     * implement for every possible renderer.
     *
     * Renderer implementations are responsible for implementing the functions
     * which generate the code which works for them.
     *
     * Shader Builders can be used for a number of purposes.
     *
     * 1) For starters, they make it easy to beginners to write simple shaders.
     * 2) Components, such as gizmos, can provide recipes for shaders, without
     *      concerning themselves with the rendering technology (OpenGL, Vulkan,
     *      DirectX, something else)
     */
    class IShaderBuilder {
    public:
        virtual std::optional<std::string> make(const ShaderBlueprint &blueprint,
                                                ShaderStage shaderStage) noexcept(false) = 0;
    };
}
