#include "opengl-renderer/opengl-renderer.hpp"

#include "zeronetics/core/tensors.h"
#include "zeronetics/logging/logging.h"

#include <glad/glad.h>
// Keep space between glad and GLFW, otherwise clang-format
// will re-arrange their order, which causes inclusion conflicts.
#include <GLFW/glfw3.h>

#include <stdexcept>

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

    glBindVertexArray(1);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
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

    // Create vertex buffer object (VBO) and vertex array object (VAO)
    GLuint VBO, VAO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    // Bind VAO first, then bind and set VBO, and then configure vertex attributes
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (0 * sizeof(GLfloat)));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

bool ZEN::OpenGLRenderer::isInitialized() const noexcept {
    return m_initialized;
}

void ZEN::OpenGLRenderer::clear() noexcept {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
