#include "zeronetics/core/controls.h"
#include "glfw-window/glfw-window.h"

#include <stdexcept>
#include <optional>

#include <GLFW/glfw3.h>

GLFWwindow *glfwWindow;

std::shared_ptr<ZEN::IInputManager> s_inputManager;

std::optional<ZEN::KeyEvent> createKeyEvent(int key, int action) {
    std::optional<ZEN::Key> inputKey = ZEN::KeyMap::toKey(key);
    if (!inputKey.has_value()) {
        return std::nullopt;
    }

    return ZEN::KeyEvent{
            .keyState = action == 1 ? ZEN::KeyState::JustPressed : ZEN::KeyState::JustReleased,
            .key = inputKey.value(),
    };
}

void keyboardCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (action > 1 || !s_inputManager) {
        return;
    }

    std::optional<ZEN::KeyEvent> keyEvent = createKeyEvent(key, action);
    if (keyEvent.has_value()) {
        s_inputManager->onKeyStateChanged(keyEvent.value());
    }
}

void ZEN::Window::generate(const ZEN::Settings &settings) noexcept(false) {
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW.");
    }

    glfwWindow = glfwCreateWindow(settings.screenResolution.w,
                                  settings.screenResolution.h,
                                  windowTitle,
                                  nullptr,
                                  nullptr);

    glfwSetKeyCallback(glfwWindow, keyboardCallback);
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

void ZEN::Window::setInputManager(const std::shared_ptr<IInputManager> &inputManager) {
    s_inputManager = inputManager;
}
