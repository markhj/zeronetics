#pragma once

#include "zeronetics/contracts/shader-builder.h"
#include "zeronetics/core/vertices.h"

#include <optional>

namespace ZEN {
    class GLSLShaderBuilder : public IShaderBuilder {
    public:
        std::optional<std::string> make(const ShaderBlueprint &blueprint,
                                        ShaderStage shaderStage) noexcept(false) override;

    private:
        uint8_t m_indentation = 0;

        std::string m_indentChar = "    ";

        std::string m_source;

        bool m_readyForNewSection = false;

        inline void add(const std::string &line,
                        bool newLine = true) noexcept;

        inline void section() noexcept;

        inline void indent() noexcept;

        inline void dedent() noexcept;

        void vertex(const ShaderBlueprint &blueprint) noexcept(false);

        void fragment(const ShaderBlueprint &blueprint) noexcept(false);
    };
}
