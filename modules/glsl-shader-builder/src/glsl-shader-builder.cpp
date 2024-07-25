#include "glsl-shader-builder/glsl-shader-builder.h"
#include <format>

#include "zeronetics/logging/logging.h"
#include "zeronetics/helpers/strings.h"

std::optional<std::string> ZEN::GLSLShaderBuilder::make(const ShaderBlueprint &blueprint,
                                                        ShaderStage shaderStage) noexcept(false) {
    if (blueprint.attributes.empty()) {
        ZEN_CRITICAL("Cannot build shader source without attributes.");
        return std::nullopt;
    }

    m_source.clear();
    m_source.reserve(500);

    switch (shaderStage) {
        case ShaderStage::Vertex:
            vertex(blueprint);
            return m_source;
        case ShaderStage::Fragment:
            fragment(blueprint);
            return m_source;
        default:
            ZEN_LIB_ERROR("Missing shader stage implementation in GLSL Shader Builder.");
            return std::nullopt;
    }
}

void ZEN::GLSLShaderBuilder::vertex(const ShaderBlueprint &blueprint) noexcept(false) {
    // Version
    add("#version 330 core");

    // Layouts
    uint8_t i = 0;
    for (const VertexAttribute &attribute: blueprint.attributes) {
        add(std::format("layout (location = {}) in vec{} a{};",
                        i,
                        VertexAttrSize::getSize(attribute),
                        VertexAttrName::getAsString(attribute)));
        ++i;
    }

    // Out
    section();
    for (const VertexAttribute &attribute: blueprint.attributes) {
        add(std::format("out vec{} {};",
                        VertexAttrSize::getSize(attribute),
                        toLowerCase(VertexAttrName::getAsString(attribute))));
    }

    // Uniform values
    section();
    if (blueprint.projection == Projection::Perspective) {
        add("uniform mat4 view;");
        add("uniform mat4 model;");
        add("uniform mat4 projection;");
    }

    // Main function
    section();
    add("void main() {");
    indent();
    if (blueprint.projection == Projection::Perspective) {
        add("gl_Position = projection * view * model * vec4(aPosition, 1.0);");
    } else {
        add("gl_Position = vec4(aPosition, 1.0);");
    }

    // Map the "out" declarations
    for (const VertexAttribute &attribute: blueprint.attributes) {
        std::string name = VertexAttrName::getAsString(attribute);
        add(std::format("{} = a{};", toLowerCase(name), name));
    }

    dedent();
    add("}", false);
}

void ZEN::GLSLShaderBuilder::fragment(const ShaderBlueprint &blueprint) noexcept(false) {
    add("#version 330 core");

    // Out
    section();
    add("out vec4 FragColor;");

    // In
    section();
    for (const VertexAttribute &attribute: blueprint.attributes) {
        add(std::format("in vec{} {};",
                        VertexAttrSize::getSize(attribute),
                        toLowerCase(VertexAttrName::getAsString(attribute))));
    }

    std::optional<uint8_t> colorSize;
    for (const VertexAttribute &attribute: blueprint.attributes) {
        if (attribute == VertexAttribute::ColorRGB) {
            colorSize = 3;
            break;
        }
    }

    // Main function
    section();
    add("void main() {");
    indent();
    if (colorSize.has_value()) {
        add("FragColor = vec4(color, 1.0);");
    } else {
        add("FragColor = vec4(1.0, 1.0, 1.0, 1.0);");
    }
    dedent();
    add("}", false);
}

void ZEN::GLSLShaderBuilder::add(const std::string &line,
                                 bool newLine) noexcept {
    for (uint8_t i = 0; i < m_indentation; ++i) {
        m_source += m_indentChar;
    }
    m_source += line + (newLine ? "\n" : "");
    m_readyForNewSection = true;
}

void ZEN::GLSLShaderBuilder::indent() noexcept {
    ++m_indentation;
}

void ZEN::GLSLShaderBuilder::dedent() noexcept {
    --m_indentation;
}

void ZEN::GLSLShaderBuilder::section() noexcept {
    if (!m_readyForNewSection) {
        return;
    }
    add("");
    m_readyForNewSection = false;
}
