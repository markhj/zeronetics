#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"
#include "opengl-renderer/opengl.hpp"
#include "zeronetics/logging/logging.h"
#include <format>
#include <iostream>

namespace {
    GLuint s_programId;

    void checkInitializationStatus() {
        if (glad_glCreateShader == nullptr) {
            ZEN_CRITICAL("You must initialize the OpenGL renderer before creating shaders.");
        }
    }

    GLenum shaderStageToGL(ZEN::ShaderStage stage) {
        switch (stage) {
            case ZEN::ShaderStage::Vertex:
                return GL_VERTEX_SHADER;
            case ZEN::ShaderStage::Fragment:
                return GL_FRAGMENT_SHADER;
            case ZEN::ShaderStage::Compute:
                return GL_COMPUTE_SHADER;
            case ZEN::ShaderStage::Geometry:
                return GL_GEOMETRY_SHADER;
            case ZEN::ShaderStage::TessControl:
                return GL_TESS_CONTROL_SHADER;
            case ZEN::ShaderStage::TessEvaluation:
                return GL_TESS_EVALUATION_SHADER;
            default:
                ZEN_LIB_ERROR("Missing shader stage in OpenGL shader implementation.");
                return 0;
        }
    }

    inline int getUniformLocation(const std::string &location) {
        return glGetUniformLocation(s_programId, location.c_str());
    }
}

void ZEN::Shader::compile() noexcept(false) {
    checkInitializationStatus();

    for (const auto &source: sources) {
        GLenum stage = shaderStageToGL(source.first);
        GLuint shader = glCreateShader(stage);
        const char *cstr = source.second.c_str();
        glShaderSource(shader, 1, &cstr, nullptr);
        glCompileShader(shader);

        GLint success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            GLchar infoLog[1024];
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            throw std::runtime_error(std::format("Shader compilation error: {}", infoLog));
        }

        glAttachShader(s_programId, shader);

        ZEN_INFO(std::format("Shader {}: Compiled {} with source: {}...", s_programId, stage, source.second.substr(0, 70)),
                 ZEN::LogCategory::ShaderCompilation);

        glDeleteShader(shader);
    }

    glLinkProgram(s_programId);

    GLint linkSuccess;
    glGetProgramiv(s_programId, GL_LINK_STATUS, &linkSuccess);
    if (!linkSuccess) {
        GLchar infoLog[1024];
        glGetProgramInfoLog(s_programId, 1024, nullptr, infoLog);
        throw std::runtime_error(std::format("Shader linking error: {}", infoLog));
    }

    ZEN_INFO(std::format("Shader {} linked.", s_programId), ZEN::LogCategory::ShaderCompilation);
}

void ZEN::Shader::setSource(ZEN::ShaderStage shaderStage, const std::string &source) noexcept {
    sources[shaderStage] = source;
}

ZEN::Shader::Shader() {
    checkInitializationStatus();
}

ZEN::Shader::~Shader() {
    glDeleteProgram(s_programId);
}

void ZEN::Shader::use() noexcept {
    glUseProgram(s_programId);
}

void ZEN::Shader::create() noexcept(false) {
    checkInitializationStatus();

    s_programId = glCreateProgram();

    ZEN_INFO(std::format("Shader program created with ID: {}", s_programId),
             ZEN::LogCategory::ShaderCompilation);
}

void ZEN::Shader::bindTo(gl_uint context) {
    glUseProgram(context);
}

ZEN::gl_uint ZEN::Shader::getContextId() const {
    return s_programId;
}

std::optional<ZEN::gl_uint> ZEN::Shader::getCurrentContextId() const {
    GLint currentProgram = 0;
    glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
    return currentProgram;
}

void ZEN::Shader::set(const std::string &location, bool value) noexcept {
    with([&]() {
        glUniform1i(getUniformLocation(location), value ? 1 : 0);
    });
}

void ZEN::Shader::set(const std::string &location, int value) noexcept {
    with([&]() {
        glUniform1i(getUniformLocation(location), value);
    });
}

void ZEN::Shader::set(const std::string &location, float value) noexcept {
    with([&]() {
        glUniform1f(getUniformLocation(location), value);
    });
}

void ZEN::Shader::set(const std::string &location, ZEN::Vec2 value) noexcept {
    with([&]() {
        glUniform2fv(getUniformLocation(location), 1, glm::value_ptr(value));
    });
}

void ZEN::Shader::set(const std::string &location, ZEN::Vec3 value) noexcept {
    with([&]() {
        glUniform3fv(getUniformLocation(location), 1, glm::value_ptr(value));
    });
}

void ZEN::Shader::set(const std::string &location, ZEN::Vec4 value) noexcept {
    with([&]() {
        glUniform4fv(getUniformLocation(location), 1, glm::value_ptr(value));
    });
}

void ZEN::Shader::set(const std::string &location, ZEN::Mat4x4 value) noexcept {
    with([&]() {
        glUniformMatrix4fv(getUniformLocation(location.c_str()),
                           1,
                           GL_FALSE,
                           glm::value_ptr(value));
    });
}
