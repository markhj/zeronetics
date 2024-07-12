#include "opengl-renderer/opengl-renderer.hpp"

#include <glad/glad.h>
// Keep space between glad and GLFW, otherwise clang-format
// will re-arrange their order, which causes inclusion conflicts.
#include <GLFW/glfw3.h>

#include <format>
#include <iostream>
#include <stdexcept>

void ZEN::OpenGLRenderer::render() {
    glUseProgram(3);

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

    out vec3 color;

    void main()
    {
        color = aColor;
        gl_Position = vec4(aPos, 1.0);
    }
)";

    // Fragment shader source code
    const char* fragmentShaderSource = R"(
    #version 330 core
    out vec4 FragColor;
    in vec3 color;
    void main()
    {
        FragColor = vec4(color, 1.0);
    }
)";

    // Compile and link the shader program
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    GLint success;
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar infoLog[1024];
        glGetShaderInfoLog(fragmentShader, 1024, nullptr, infoLog);
        throw std::runtime_error(std::format("Shader compile/linking error: {}", infoLog));
    }

    GLuint shaderProgram = glCreateProgram();
    std::cout << shaderProgram;
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    GLint successX;
    glGetProgramiv(1, GL_LINK_STATUS, &successX);
    if (!successX) {
        GLchar infoLog[1024];
        glGetProgramInfoLog(1, 1024, nullptr, infoLog);
        throw std::runtime_error(std::format("Shader compile/linking error: {}", infoLog));
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

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
