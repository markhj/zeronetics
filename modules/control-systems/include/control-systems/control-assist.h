#pragma once

#include "zeronetics/contracts/input-manager.h"
#include <functional>

namespace ZEN::ControlSystems {
    /**
     * Mapping of user inputs across various control interfaces.
     *
     * @ref control-systems
     */
    class InputMapping {
    public:
        /**
         * Signal to be given when a key has just been pressed.
         *
         * @param key
         * @param signal
         */
        void keyJustPressed(Key key, const char *signal) noexcept;

        /**
         * Signal to be sent, when a key is just released.
         *
         * @param key
         * @param signal
         */
        void keyJustReleased(Key key, const char* signal) noexcept;

        /**
         * Signal to be sent, while a key is held down
         */
        void keyDown(Key key, const char* signal) noexcept;

        /**
         * Retrieve the signal based on a ZEN::KeyStateEvent.
         *
         * @param keyStateEvent
         * @return
         */
        [[nodiscard]] std::optional<const char *> getSignal(const KeyStateEvent &keyStateEvent) const noexcept;

        /**
         * Retrieve signal for when a key is held down.
         *
         * @param keyDownEvent
         * @return
         */
        [[nodiscard]] std::optional<const char *> getSignal(const KeyDownEvent &keyDownEvent) const noexcept;

    private:
        enum Form {
            KeyPressed,
            KeyReleased,
            KeyDown,
        };

        struct InputMap {
            Form form;
            Key key;
            const char *signal;
        };

        std::vector<InputMap> m_mapping;
    };

    /**
     * Signal handler
     *
     * @ref control-systems
     */
    class SignalHandler {
    public:
        /**
         * The action to be taken, when ``signal`` is received.
         *
         * @param signal
         * @param handle
         */
        void on(const char *signal, const std::function<void()> &handle) noexcept;

        /**
         * Invoke/execute the handler associated with a signal.
         *
         * @note If no signal is defined, no actions will be taken.
         *      But a ZEN_WARN will be raised.
         *
         * @note It cannot be guaranteed that exceptions aren't thrown from the handlers.
         *
         * @param signal
         */
        void invoke(const char *signal) noexcept(false);

    private:
        std::unordered_map<const char *, std::function<void()>> handles;
    };

    /**
     * A more fully-fledged implementation of ZEN::IInputManager, which
     * helps you manage a wider range of controls "out of the box",
     * utilizing an easy m_mapping system.
     *
     * @ref control-systems
     */
    class ControlManager : public IInputManager {
    public:
        /**
         * Current input m_mapping, if any
         */
        std::shared_ptr<InputMapping> inputMapping;

        /**
         * Current signal handler, if any
         */
        std::shared_ptr<SignalHandler> signalHandler;

    private:
        void process(dt_float delta) override;

        void onKeyStateChanged(const KeyStateEvent &keyEvent) override;

        void onMouseMoved(const MouseMovedEvent &mouseMovedEvent) override;

        std::vector<Key> m_keysDown;
    };
}
