#include <format>

#include "zeronetics/core/enums.h"
#include "zeronetics/core/vertices.h"
#include "zeronetics/logging/logging.h"

#include "vao.h"

#include "glad/glad.h"

void ZEN::OpenGL::VAO::initialize() noexcept(false) {
    glGenVertexArrays(1, &id);
    ZEN_INFO(std::format("OpenGL: Created VAO: {}", id), ZEN::LogCategory::RendererInit);
}

void ZEN::OpenGL::VAO::attachVBO(const std::shared_ptr<VBO> &vbo,
                         const std::vector<ZEN::VertexAttribute> &attributes) noexcept(false) {
    int vertexSize = 0;
    for (const auto &item: attributes) {
        vertexSize += ZEN::VertexAttrSize::getSize(item);
    }

    m_vbos.push_back(vbo);
    with([&]() {
        vbo->with([&]() {
            unsigned int i = 0, ptrIndex = 0;
            std::for_each(attributes.begin(), attributes.end(), [&](const ZEN::VertexAttribute &attr) {
                uint8_t attrSize = ZEN::VertexAttrSize::getSize(attr);
                glVertexAttribPointer(i,
                                      attrSize,
                                      GL_FLOAT,
                                      GL_FALSE,
                                      vertexSize * sizeof(float),
                                      (void *) (ptrIndex * sizeof(GLfloat)));
                glEnableVertexAttribArray(i);
                ++i;
                ptrIndex += attrSize;
            });

            ZEN_INFO(std::format("VAO {} and VBO {} connected with vertex size of {} across {} attributes.",
                                 getContextId(),
                                 vbo->getContextId(),
                                 vertexSize,
                                 i),
                     ZEN::LogCategory::RendererInit);
        });
    });
}

std::optional<ZEN::OpenGL::gl_uint> ZEN::OpenGL::VAO::getCurrentContextId() const {
    gl_int currentVAO;
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &currentVAO);
    return currentVAO;
}

void ZEN::OpenGL::VAO::bindTo(ZEN::OpenGL::gl_uint context) {
    glBindVertexArray(context);
}

ZEN::OpenGL::gl_uint ZEN::OpenGL::VAO::getContextId() const {
    return id;
}
