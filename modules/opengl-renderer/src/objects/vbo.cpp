#include "vbo.h"
#include <format>

#include "glad/glad.h"
#include "zeronetics/logging/logging.h"

void ZEN::VBO::initialize() noexcept(false) {
    glGenBuffers(1, &id);
    ZEN_INFO(std::format("OpenGL: Created VBO: {}", id), ZEN::LogCategory::RendererInit);
}

std::optional<ZEN::gl_uint> ZEN::VBO::getCurrentContextId() const {
    GLint currentVBO;
    glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &currentVBO);
    return currentVBO;
}

void ZEN::VBO::bindTo(ZEN::gl_uint context) {
    glBindBuffer(GL_ARRAY_BUFFER, context);
}

ZEN::gl_uint ZEN::VBO::getContextId() const {
    return id;
}
