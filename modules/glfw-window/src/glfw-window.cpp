#include "glfw-window/glfw-window.h"
#include <stdexcept>

#include <GLFW/glfw3.h>

GLFWwindow *glfwWindow;

void ZEN::Window::generate(const ZEN::Settings &settings) noexcept(false) {
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW.");
    }

    glfwWindow = glfwCreateWindow(settings.screenResolution.w,
                                  settings.screenResolution.h,
                                  "Game",
                                  nullptr,
                                  nullptr);
}

void ZEN::Window::regenerate(const ZEN::Settings &settings) noexcept(false) {

}

void ZEN::Window::close() noexcept {
    glfwDestroyWindow(glfwWindow);
}

ZEN::Window::~Window() {
    glfwTerminate();
}

void ZEN::Window::handleInputs() {
    glfwPollEvents();
}

void ZEN::Window::handleBuffer() {
    glfwSwapBuffers(glfwWindow);
}
