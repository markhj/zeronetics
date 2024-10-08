#include "glfw-window/glfw-window.h"
#include "zeronetics/core/globals.h"
#include "zeronetics/core/inputs.h"
#include "zeronetics/logging/logging.h"

#include <optional>
#include <stdexcept>

#include <GLFW/glfw3.h>
#include <iostream>

namespace {
    GLFWwindow *glfwWindow;

    std::shared_ptr<ZEN::IInputManager> s_inputManager;

    std::optional<ZEN::MousePosition> s_lastPosition;

    std::optional<std::function<void()>> s_onCloseHandle;

    std::optional<std::function<void()>> s_onResizeHandle;

    inline int getSamples(const ZEN::AntiAlias &antiAlias) {
        switch (antiAlias) {
            case ZEN::AntiAlias::None:
                return 0;
            case ZEN::AntiAlias::MSAA2X:
                return 2;
            case ZEN::AntiAlias::MSAA4X:
                return 4;
            case ZEN::AntiAlias::MSAA8X:
                return 8;
            default:
                ZEN_LIB_ERROR("GLFW Window: Missing case in getSamples.");
                return 0;
        }
    }

    std::optional<ZEN::KeyStateEvent> createKeyEvent(int key, int action) {
        std::optional<ZEN::Key> inputKey = ZEN::KeyMap::toKey(key);
        if (!inputKey.has_value()) {
            return std::nullopt;
        }

        return ZEN::KeyStateEvent{
                .keyState = action == 1 ? ZEN::KeyState::JustPressed : ZEN::KeyState::JustReleased,
                .key = inputKey.value(),
        };
    }

    void keyboardCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
        if (action > 1 || !s_inputManager) {
            return;
        }

        std::optional<ZEN::KeyStateEvent> keyEvent = createKeyEvent(key, action);
        if (keyEvent.has_value()) {
            s_inputManager->onKeyStateChanged(keyEvent.value());
        }
    }

    void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
        if (action > 1 || !s_inputManager) {
            return;
        }

        ZEN::MouseButton mouseButton;
        switch (button) {
            case 0:
                mouseButton = ZEN::MouseButton::PrimaryMouseButton;
                break;
            case 1:
                mouseButton = ZEN::MouseButton::SecondaryMouseButton;
                break;
            case 2:
                mouseButton = ZEN::MouseButton::MiddleMouseButton;
                break;
            default:
                return;
        }

        s_inputManager->onMouseButtonStateChanged({
                .mouseButtonState = action == 1 ? ZEN::MouseButtonState::JustClicked : ZEN::MouseButtonState::JustReleased,
                .mouseButton = mouseButton,
        });
    }

    void mouseWheelCallback(GLFWwindow *glfwWindow, double x, double y) {
        // @todo: Implement mouse wheel callback
    }

    void framebufferSizeCallback(GLFWwindow *glfwWindow, int width, int height) {
        ZEN::Globals::viewportSize.w = static_cast<uint16_t>(width);
        ZEN::Globals::viewportSize.h = static_cast<uint16_t>(height);
        if (s_onResizeHandle.has_value()) {
            s_onResizeHandle.value()();
        }
    }

    void mouseMoveCallback(GLFWwindow *window, double x, double y) {
        if (!s_inputManager) {
            return;
        }

        auto mx = static_cast<ZEN::mouse_pos_axis>(x);
        auto my = static_cast<ZEN::mouse_pos_axis>(y);

        // If the mouse position has not yet been recorded,
        // we start by setting the current position in the s_lastPosition,
        // and then abandon ship
        if (!s_lastPosition.has_value()) {
            s_lastPosition = {mx, my};
            return;
        }

        ZEN::MousePosition lastPos = s_lastPosition.value();

        s_inputManager->onMouseMoved({
                {mx, my},
                {static_cast<ZEN::mouse_pos_axis>(mx - lastPos.x),
                 static_cast<ZEN::mouse_pos_axis>(my - lastPos.y)},
        });

        s_lastPosition = {mx, my};
    }

    void closeWindowCallback(GLFWwindow *window) {
        if (s_onCloseHandle.has_value()) {
            s_onCloseHandle.value()();
        }
    }
}

void ZEN::Window::generate(const ZEN::Settings &settings) noexcept(false) {
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW.");
    }

    glfwWindowHint(GLFW_SAMPLES, getSamples(settings.antiAlias));

    glfwWindow = glfwCreateWindow(settings.screenResolution.w,
                                  settings.screenResolution.h,
                                  windowTitle,
                                  nullptr,
                                  nullptr);

    glfwSwapInterval(settings.vSync ? 1 : 0);

    ZEN::Globals::viewportSize = settings.screenResolution;

    glfwMakeContextCurrent(glfwWindow);

    // Window-specific callbacks
    glfwSetWindowCloseCallback(glfwWindow, closeWindowCallback);
    glfwSetFramebufferSizeCallback(glfwWindow, framebufferSizeCallback);

    // Keyboard
    glfwSetKeyCallback(glfwWindow, keyboardCallback);

    // Mouse
    glfwSetCursorPosCallback(glfwWindow, mouseMoveCallback);
    glfwSetMouseButtonCallback(glfwWindow, mouseButtonCallback);
    glfwSetScrollCallback(glfwWindow, mouseWheelCallback);
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

void ZEN::Window::onClose(std::function<void()> handle) {
    s_onCloseHandle = handle;
}

void ZEN::Window::process(ZEN::dt_float delta) {
    if (s_inputManager) {
        s_inputManager->process(delta);
    }
}

void ZEN::Window::onResize(std::function<void()> handle) {
    s_onResizeHandle = handle;
}
