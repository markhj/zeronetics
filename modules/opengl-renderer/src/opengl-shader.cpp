#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"
#include "opengl-renderer/opengl.h"
#include "zeronetics/logging/logging.h"
#include <format>
#include <iostream>

namespace {
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
}

void ZEN::OpenGL::Shader::compile() noexcept(false) {
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

        glAttachShader(m_programId, shader);

        ZEN_INFO(std::format("Shader {}: Compiled {} with source: {}...", m_programId, stage, source.second.substr(0, 300)),
                 ZEN::LogCategory::ShaderCompilation);

        glDeleteShader(shader);
    }

    glLinkProgram(m_programId);

    GLint linkSuccess;
    glGetProgramiv(m_programId, GL_LINK_STATUS, &linkSuccess);
    if (!linkSuccess) {
        GLchar infoLog[1024];
        glGetProgramInfoLog(m_programId, 1024, nullptr, infoLog);
        throw std::runtime_error(std::format("Shader linking error: {}", infoLog));
    }

    ZEN_INFO(std::format("Shader {} linked.", m_programId), ZEN::LogCategory::ShaderCompilation);
}

void ZEN::OpenGL::Shader::setSource(ZEN::ShaderStage shaderStage, const std::string &source) noexcept {
    sources[shaderStage] = source;
}

ZEN::OpenGL::Shader::Shader() {
    checkInitializationStatus();
}

ZEN::OpenGL::Shader::~Shader() {
    glDeleteProgram(m_programId);
}

void ZEN::OpenGL::Shader::use() noexcept {
    glUseProgram(m_programId);
}

void ZEN::OpenGL::Shader::create() noexcept(false) {
    checkInitializationStatus();

    m_programId = glCreateProgram();

    ZEN_INFO(std::format("Shader program created with ID: {}", m_programId),
             ZEN::LogCategory::ShaderCompilation);
}

void ZEN::OpenGL::Shader::bindTo(gl_uint context) {
    glUseProgram(context);
}

ZEN::OpenGL::gl_uint ZEN::OpenGL::Shader::getContextId() const {
    return m_programId;
}

std::optional<ZEN::OpenGL::gl_uint> ZEN::OpenGL::Shader::getCurrentContextId() const {
    GLint currentProgram = 0;
    glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
    return currentProgram;
}

void ZEN::OpenGL::Shader::set(const std::string &location, bool value) noexcept {
    with([&]() {
        glUniform1i(glGetUniformLocation(m_programId, location.c_str()), value ? 1 : 0);
    });
}

void ZEN::OpenGL::Shader::set(const std::string &location, int value) noexcept {
    with([&]() {
        glUniform1i(glGetUniformLocation(m_programId, location.c_str()), value);
    });
}

void ZEN::OpenGL::Shader::set(const std::string &location, float value) noexcept {
    with([&]() {
        glUniform1f(glGetUniformLocation(m_programId, location.c_str()), value);
    });
}

void ZEN::OpenGL::Shader::set(const std::string &location, ZEN::Vec2 value) noexcept {
    with([&]() {
        glUniform2fv(glGetUniformLocation(m_programId, location.c_str()), 1, glm::value_ptr(value));
    });
}

void ZEN::OpenGL::Shader::set(const std::string &location, ZEN::Vec3 value) noexcept {
    with([&]() {
        glUniform3fv(glGetUniformLocation(m_programId, location.c_str()), 1, glm::value_ptr(value));
    });
}

void ZEN::OpenGL::Shader::set(const std::string &location, ZEN::Vec4 value) noexcept {
    with([&]() {
        glUniform4fv(glGetUniformLocation(m_programId, location.c_str()), 1, glm::value_ptr(value));
    });
}

void ZEN::OpenGL::Shader::set(const std::string &location, ZEN::Mat4x4 value) noexcept {
    with([&]() {
        glUniformMatrix4fv(glGetUniformLocation(m_programId, location.c_str()),
                           1,
                           GL_FALSE,
                           glm::value_ptr(value));
    });
}
