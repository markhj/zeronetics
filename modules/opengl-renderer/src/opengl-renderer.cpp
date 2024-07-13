#include "opengl-renderer/opengl.hpp"

#include "objects/vao.h"
#include "objects/vbo.h"

#include "zeronetics/core/tensors.h"
#include "zeronetics/logging/logging.h"

#include <glad/glad.h>
// Keep space between glad and GLFW, otherwise clang-format
// will re-arrange their order, which causes inclusion conflicts.
#include <GLFW/glfw3.h>

#include <stdexcept>

namespace {
    ZEN::VAO vao;
    std::shared_ptr<ZEN::VBO> vbo;
}

void ZEN::OpenGLRenderer::render() {
    if (!renderManager) {
        ZEN_WARN("No render manager provided", ZEN::LogCategory::Rendering);
    }

    auto targetShader = renderManager->shaders["MyShader"];

    if (renderManager->camera3d) {
        MVP mvp = renderManager->camera3d->getModelViewProjection();

        targetShader->set("model", mvp.model);
        targetShader->set("view", mvp.view);
        targetShader->set("projection", mvp.projection);
    }

    targetShader->use();

    vao.with([&]() {
        glDrawArrays(GL_TRIANGLES, 0, 3);
    });
}

void ZEN::OpenGLRenderer::initialize() {
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD.");
    }

    m_initialized = true;

    // Vertex data
    float vertices[] = {
            -0.5f, -0.5f, 0.0f, 1.0, 0.0, 0.0,
            0.5f, -0.5f, 0.0f, 0.0, 1.0, 0.0,
            0.0f, 0.5f, 0.0f, 0.0, 0.0, 1.0};

    vbo = std::make_shared<VBO>(VBO());
    vbo->initialize();

    vao.initialize();
    vao.attachVBO(vbo, {VertexAttribute::Position3D, VertexAttribute::ColorRGB});

    vbo->bind();
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    vbo->unbind();
}

bool ZEN::OpenGLRenderer::isInitialized() const noexcept {
    return m_initialized;
}

void ZEN::OpenGLRenderer::clear() noexcept {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
