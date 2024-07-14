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

void ZEN::VBO::setData(std::vector<gl_float> data) {
    with([&]() {
        glBufferData(GL_ARRAY_BUFFER, currentSize * sizeof(GLfloat), data.data(), GL_STATIC_DRAW);
    });
}

void ZEN::VBO::resize(ZEN::gpu_alloc_int size) {
    auto oldSize = currentSize;
    with([&]() {
        glBufferData(GL_ARRAY_BUFFER, currentSize * sizeof(GLfloat), {}, GL_STATIC_DRAW);
    });
    currentSize = size;
    currentAllocIndex = 0;

    ZEN_INFO(std::format("VBO {} resized from {} to {}", id, oldSize, currentSize),
             ZEN::LogCategory::RendererInternals);
}

std::optional<ZEN::GPUAllocation> ZEN::VBO::allocate(ZEN::gpu_alloc_int size) {
    if (currentAllocIndex + size > currentSize) {
        return std::nullopt;
    }
    GPUAllocation result {currentAllocIndex, size};
    currentAllocIndex += size;
    return result;
}

ZEN::gpu_alloc_int ZEN::VBO::getCurrentSize() const noexcept {
    return currentSize;
}
