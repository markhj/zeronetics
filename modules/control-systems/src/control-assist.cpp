#include "control-systems/control-assist.h"
#include "zeronetics/logging/log.h"
#include "zeronetics/logging/logging.h"
#include <format>

void ZEN::ControlSystems::ControlManager::onKeyStateChanged(const KeyStateEvent &keyEvent) {
    auto it = std::find(m_keysDown.begin(), m_keysDown.end(), keyEvent.key);
    if (it != m_keysDown.end() && keyEvent.keyState == KeyState::JustReleased) {
        m_keysDown.erase(it);
    } else if (it == m_keysDown.end() && keyEvent.keyState == KeyState::JustPressed) {
        m_keysDown.emplace_back(keyEvent.key);
    }

    if (!inputMapping || !signalHandler) {
        return;
    }

    std::optional<const char *> signal = inputMapping->getSignal(keyEvent);
    if (!signal.has_value()) {
        return;
    }

    signalHandler->invoke(signal.value());
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
            signalHandler->invoke(signal.value());
        }
    });
}

void ZEN::ControlSystems::InputMapping::keyJustPressed(ZEN::Key key, const char *signal) noexcept {
    m_mapping.push_back({Form::KeyPressed, key, signal});
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
    m_mapping.push_back({Form::KeyReleased, key, signal});
}

void ZEN::ControlSystems::InputMapping::keyDown(ZEN::Key key, const char *signal) noexcept {
    m_mapping.push_back({Form::KeyDown, key, signal});
}

std::optional<const char *> ZEN::ControlSystems::InputMapping::getSignal(const ZEN::KeyDownEvent &keyDownEvent) const noexcept {
    for (const auto &item: m_mapping) {
        if (item.form == Form::KeyDown && item.key == keyDownEvent.key) {
            return item.signal;
        }
    }
    return std::nullopt;
}

void ZEN::ControlSystems::SignalHandler::on(const char *signal, const std::function<void()> &handle) noexcept {
    handles[signal] = handle;
}

void ZEN::ControlSystems::SignalHandler::invoke(const char *signal) noexcept(false) {
    if (!handles.contains(signal)) {
        ZEN_WARN(std::format("Attempting to invoke non-existing signal: {}", signal),
                 ZEN::LogCategory::Controls);
        return;
    }
    handles[signal]();
}
