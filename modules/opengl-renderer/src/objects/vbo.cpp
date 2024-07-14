#include "vbo.h"
#include <format>

#include "glad/glad.h"
#include "zeronetics/logging/logging.h"

void ZEN::OpenGL::VBO::initialize() noexcept(false) {
    glGenBuffers(1, &id);
    ZEN_INFO(std::format("OpenGL: Created VBO: {}", id), ZEN::LogCategory::RendererInit);
}

std::optional<ZEN::OpenGL::gl_uint> ZEN::OpenGL::VBO::getCurrentContextId() const {
    GLint currentVBO;
    glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &currentVBO);
    return currentVBO;
}

void ZEN::OpenGL::VBO::bindTo(ZEN::OpenGL::gl_uint context) {
    glBindBuffer(GL_ARRAY_BUFFER, context);
}

ZEN::OpenGL::gl_uint ZEN::OpenGL::VBO::getContextId() const {
    return id;
}

void ZEN::OpenGL::VBO::setData(std::vector<gl_float> data) {
    with([&]() {
        glBufferSubData(GL_ARRAY_BUFFER,
                        0,
                        data.size() * sizeof(GLfloat),
                        data.data());
    });
}

void ZEN::OpenGL::VBO::updateData(const ZEN::GPUAllocation &allocation, const std::vector<gl_float> &data) {
    with([&]() {
        glBufferSubData(GL_ARRAY_BUFFER,
                        allocation.index * sizeof(GLfloat),
                        allocation.size * sizeof(GLfloat),
                        data.data());
    });
}

void ZEN::OpenGL::VBO::resize(ZEN::gpu_alloc_int size) {
    auto oldSize = currentSize;
    with([&]() {
        std::vector<float> n;
        while (n.size() < size) {
            n.emplace_back(0.0);
        }
        glBufferData(GL_ARRAY_BUFFER, size * sizeof(GLfloat), n.data(), GL_DYNAMIC_DRAW);
    });
    currentSize = size;
    currentAllocIndex = 0;

    ZEN_INFO(std::format("VBO {} resized from {} to {}", id, oldSize, currentSize),
             ZEN::LogCategory::RendererInternals);
}

std::optional<ZEN::GPUAllocation> ZEN::OpenGL::VBO::allocate(ZEN::gpu_alloc_int size) {
    if (currentAllocIndex + size > currentSize) {
        return std::nullopt;
    }
    GPUAllocation result{currentAllocIndex, size};
    currentAllocIndex += size;
    return result;
}

ZEN::gpu_alloc_int ZEN::OpenGL::VBO::getCurrentSize() const noexcept {
    return currentSize;
}
