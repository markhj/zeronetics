#include "control-systems/control-assist.h"
#include "zeronetics/logging/log.h"
#include "zeronetics/logging/logging.h"
#include <format>

void ZEN::ControlSystems::ControlManager::onKeyStateChanged(const KeyStateEvent &keyEvent) {
    if (!inputMapping || !signalHandler) {
        return;
    }

    auto it = std::find(m_keysDown.begin(), m_keysDown.end(), keyEvent.key);
    if (it != m_keysDown.end() && keyEvent.keyState == KeyState::JustReleased) {
        m_keysDown.erase(it);
    } else if (it == m_keysDown.end() && keyEvent.keyState == KeyState::JustPressed) {
        m_keysDown.emplace_back(keyEvent.key);
    }

    std::optional<const char *> signal = inputMapping->getSignal(keyEvent);
    if (!signal.has_value()) {
        return;
    }

    signalHandler->invoke(signal.value(), std::nullopt);
}

void ZEN::ControlSystems::ControlManager::onMouseMoved(const MouseMovedEvent &mouseMovedEvent) {
}

void ZEN::ControlSystems::ControlManager::process(ZEN::dt_float delta) {
    if (!inputMapping || !signalHandler) {
        return;
    }

    std::for_each(m_keysDown.begin(), m_keysDown.end(), [&](const Key &key) {
        std::optional<const char *> signal = inputMapping->getSignal(KeyDownEvent{key});
        if (signal.has_value()) {
            signalHandler->invoke(signal.value(), delta);
        }
    });

    std::for_each(m_mouseButtonsDown.begin(), m_mouseButtonsDown.end(), [&](const MouseButton &mouseButton) {
        std::optional<const char *> signal = inputMapping->getSignal(MouseButtonDownEvent{mouseButton});
        if (signal.has_value()) {
            signalHandler->invoke(signal.value(), delta);
        }
    });
}

void ZEN::ControlSystems::ControlManager::onMouseButtonStateChanged(const ZEN::MouseButtonStateEvent &mouseButtonStateEvent) {
    if (!inputMapping || !signalHandler) {
        return;
    }

    auto it = std::find(m_mouseButtonsDown.begin(), m_mouseButtonsDown.end(), mouseButtonStateEvent.mouseButton);
    if (it != m_mouseButtonsDown.end() && mouseButtonStateEvent.mouseButtonState == MouseButtonState::JustReleased) {
        m_mouseButtonsDown.erase(it);
    } else if (it == m_mouseButtonsDown.end() && mouseButtonStateEvent.mouseButtonState == MouseButtonState::JustClicked) {
        m_mouseButtonsDown.emplace_back(mouseButtonStateEvent.mouseButton);
    }

    std::optional<const char *> signal = inputMapping->getSignal(mouseButtonStateEvent);
    if (!signal.has_value()) {
        return;
    }

    signalHandler->invoke(signal.value(), std::nullopt);
}

void ZEN::ControlSystems::InputMapping::keyJustPressed(ZEN::Key key, const char *signal) noexcept {
    m_mapping.push_back({
            .form = Form::KeyPressed,
            .key = key,
            .signal = signal,
    });
}

std::optional<const char *> ZEN::ControlSystems::InputMapping::getSignal(const ZEN::KeyStateEvent &keyStateEvent) const noexcept {
    for (const auto &item: m_mapping) {
        if (item.form == Form::KeyPressed && keyStateEvent.keyState == KeyState::JustPressed && item.key == keyStateEvent.key) {
            return item.signal;
        }

        if (item.form == Form::KeyReleased && keyStateEvent.keyState == KeyState::JustReleased && item.key == keyStateEvent.key) {
            return item.signal;
        }
    }
    return std::nullopt;
}

void ZEN::ControlSystems::InputMapping::keyJustReleased(ZEN::Key key, const char *signal) noexcept {
    m_mapping.push_back({.form = Form::KeyReleased,
                         .key = key,
                         .signal = signal});
}

void ZEN::ControlSystems::InputMapping::keyDown(ZEN::Key key, const char *signal) noexcept {
    m_mapping.push_back({.form = Form::KeyDown,
                         .key = key,
                         .signal = signal});
}

std::optional<const char *> ZEN::ControlSystems::InputMapping::getSignal(const ZEN::KeyDownEvent &keyDownEvent) const noexcept {
    for (const auto &item: m_mapping) {
        if (item.form == Form::KeyDown && item.key == keyDownEvent.key) {
            return item.signal;
        }
    }
    return std::nullopt;
}

void ZEN::ControlSystems::InputMapping::mouseButtonJustClicked(ZEN::MouseButton mouseButton, const char *signal) noexcept {
    m_mapping.push_back({.form = Form::MouseButtonPressed,
                         .mouseButton = mouseButton,
                         .signal = signal});
}

void ZEN::ControlSystems::InputMapping::mouseButtonJustReleased(ZEN::MouseButton mouseButton, const char *signal) noexcept {
    m_mapping.push_back({.form = Form::MouseButtonReleased,
                         .mouseButton = mouseButton,
                         .signal = signal});
}

void ZEN::ControlSystems::InputMapping::mouseButtonDown(ZEN::MouseButton mouseButton, const char *signal) noexcept {
    m_mapping.push_back({.form = Form::MouseButtonDown,
                         .mouseButton = mouseButton,
                         .signal = signal});
}

std::optional<const char *> ZEN::ControlSystems::InputMapping::getSignal(const ZEN::MouseButtonStateEvent &mouseButtonStateEvent) const noexcept {
    for (const auto &item: m_mapping) {
        if (item.form == Form::MouseButtonPressed && mouseButtonStateEvent.mouseButtonState == MouseButtonState::JustClicked && item.mouseButton == mouseButtonStateEvent.mouseButton) {
            return item.signal;
        }

        if (item.form == Form::MouseButtonReleased && mouseButtonStateEvent.mouseButtonState == MouseButtonState::JustReleased && item.mouseButton == mouseButtonStateEvent.mouseButton) {
            return item.signal;
        }
    }
    return std::nullopt;
}

std::optional<const char *> ZEN::ControlSystems::InputMapping::getSignal(const ZEN::MouseButtonDownEvent &event) const noexcept {
    for (const auto &item: m_mapping) {
        if (item.form == Form::MouseButtonDown && item.mouseButton == event.mouseButton) {
            return item.signal;
        }
    }
    return std::nullopt;
}

void ZEN::ControlSystems::SignalHandler::on(const char *signal, const std::function<void()> &handle) noexcept {
    handles[signal] = handle;
}

void ZEN::ControlSystems::SignalHandler::invoke(const char *signal,
                                                std::optional<dt_float> delta) noexcept(false) {
    if (handlesWithDelta.contains(signal) && delta.has_value()) {
        handlesWithDelta[signal](delta.value());
    } else if (handles.contains(signal)) {
        handles[signal]();
    } else {
        ZEN_WARN(std::format("Attempting to invoke non-existing signal: {}", signal),
                 ZEN::LogCategory::Controls);
    }
}

void ZEN::ControlSystems::SignalHandler::on(const char *signal, const std::function<void(dt_float)> &handle) noexcept {
    handlesWithDelta[signal] = handle;
}
