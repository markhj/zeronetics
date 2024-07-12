#include "opengl-renderer/opengl-renderer.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "zeronetics/core/tensors.h"

#include <glad/glad.h>
// Keep space between glad and GLFW, otherwise clang-format
// will re-arrange their order, which causes inclusion conflicts.
#include <GLFW/glfw3.h>

#include <format>
#include <iostream>
#include <stdexcept>

float dt = 0.0;

ZEN::Shader openGlShader;

void ZEN::OpenGLRenderer::render() {
    dt += 0.0005;

    Vec3 position(sin(dt), 1.0, cos(dt));
    Vec3 target(0.0);
    Vec3 up(0.0, 1.0, 0.0);

    auto view = glm::lookAt(position, target, up);
    auto model = glm::mat4(1.0f);

    float aspectRatio = 800.0f / 600.0f;
    float fovY = glm::radians(45.0f);
    float nearClip = 0.1f;
    float farClip = 100.0f;
    auto perspective = glm::perspective(fovY, aspectRatio, nearClip, farClip);

    std::vector<GLfloat> data = { static_cast<float>(abs(sin(dt))) };
    glBindBuffer(GL_ARRAY_BUFFER, 1);
    glBufferSubData(GL_ARRAY_BUFFER,
                    3 * sizeof(GLfloat),
                    1 * sizeof(GLfloat),
                    data.data());
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    openGlShader.use();

    openGlShader.set("model", model);
    openGlShader.set("view", view);
    openGlShader.set("projection", perspective);

    glBindVertexArray(1);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}

void ZEN::OpenGLRenderer::initialize() {
    // @todo: Temporarily allowed tight coupling between GLFW (window)
    //      and this OpenGL renderer.
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD.");
    }

    m_initialized = true;

    // Vertex shader source code
    const char* vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec3 aColor;

    uniform mat4 view;
    uniform mat4 model;
    uniform mat4 projection;

    out vec3 color;

    void main()
    {
        color = aColor;
        gl_Position = projection * view * model * vec4(aPos, 1.0);
    }
)";

    const char* fragmentShaderSource2 = R"(
    #version 330 core
    out vec4 FragColor;
    in vec3 color;
    void main()
    {
        FragColor = vec4(color, 1.0);
    }
)";

    openGlShader.create();
    openGlShader.setSource(ShaderStage::Vertex, vertexShaderSource);
    openGlShader.setSource(ShaderStage::Fragment, fragmentShaderSource2);
    openGlShader.compile();

    // Vertex data
    float vertices[] = {
            -0.5f, -0.5f, 0.0f,1.0, 0.0, 0.0,
            0.5f, -0.5f, 0.0f, 0.0, 1.0, 0.0,
            0.0f, 0.5f, 0.0f, 0.0, 0.0, 1.0
    };

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
