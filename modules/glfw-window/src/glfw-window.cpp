#include "glfw-window/glfw-window.h"
#include <stdexcept>

#include <GLFW/glfw3.h>

GLFWwindow *glfwWindow;

void ZEN::Window::generate() {
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW.");
    }

    glfwWindow = glfwCreateWindow(1024,
                                  768,
                                  "Game",
                                  nullptr,
                                  nullptr);
}
