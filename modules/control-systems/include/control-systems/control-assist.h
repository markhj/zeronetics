#pragma once

#include "zeronetics/core/typedefs.h"
#include "zeronetics/contracts/input-manager.h"

#include <functional>
#include <vector>
#include <string>

namespace ZEN::ControlSystems {
    struct AssistInitialization {
        std::vector<const char *> signals;
    };

    class Assist {
    public:
        virtual void process(dt_float delta,
                             const std::vector<std::string> &signals) = 0;

        virtual void onMouseMoved(const MouseMovedEvent &mouseMovedEvent) = 0;

        virtual void initialize() = 0;

        virtual std::vector<const char *> getSignals() = 0;

        AssistInitialization start();

        bool isInitialized() const noexcept;

    private:
        bool m_initialized = false;

    };

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
         * Signal to be sent in the moment a mouse button is clicked (not yet released).
         *
         * @param mouseButton
         * @param signal
         */
        void mouseButtonJustClicked(MouseButton mouseButton, const char *signal) noexcept;

        /**
         * Signal for the moment a mouse button is released.
         *
         * @param mouseButton
         * @param signal
         */
        void mouseButtonJustReleased(MouseButton mouseButton, const char *signal) noexcept;

        /**
         * Signal while a mouse button is held down.
         *
         * @param mouseButton
         * @param signal
         */
        void mouseButtonDown(MouseButton mouseButton, const char *signal) noexcept;

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

        /**
         * Get a signal for a mouse button state event.
         *
         * @param mouseButtonStateEvent
         * @return
         */
        [[nodiscard]] std::optional<const char *> getSignal(const MouseButtonStateEvent &mouseButtonStateEvent) const noexcept;

        /**
         * Retrieve signal for when a mouse button is held down.
         *
         * @param keyDownEvent
         * @return
         */
        [[nodiscard]] std::optional<const char *> getSignal(const MouseButtonDownEvent &event) const noexcept;

    private:
        enum Form {
            KeyPressed,
            KeyReleased,
            KeyDown,
            MouseButtonPressed,
            MouseButtonReleased,
            MouseButtonDown,
        };

        struct InputMap {
            Form form;
            Key key;
            MouseButton mouseButton;
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
         * Signals that can be processed with delta value.
         *
         * @param signal
         * @param handle
         */
        void on(const char *signal, const std::function<void(dt_float delta)> &handle) noexcept;

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
        void invoke(const char *signal, std::optional<dt_float> delta) noexcept(false);

        void lockSignals(const std::vector<const char *> &signals) noexcept;

    private:
        std::vector<const char *> m_lockedSignals;

        std::unordered_map<const char *, std::function<void()>> handles;

        std::unordered_map<const char *, std::function<void(dt_float delta)>> handlesWithDelta;
    };

    /**
     * A more fully-fledged implementation of ZEN::IInputManager, which
     * helps you manage a wider range of controls "out of the box",
     * utilizing an easy mapping system.
     *
     * @ref control-systems
     */
    class ControlManager : public IInputManager {
    public:
        void setInputMapping(const std::shared_ptr<InputMapping> &inputMapping);

        void setSignalHandler(const std::shared_ptr<SignalHandler> &signalHandler);

        void attachAssist(const std::shared_ptr<Assist> &assist) noexcept;

    private:
        void process(dt_float delta) override;

        void onKeyStateChanged(const KeyStateEvent &keyEvent) override;

        void onMouseMoved(const MouseMovedEvent &mouseMovedEvent) override;

        void onMouseButtonStateChanged(const MouseButtonStateEvent &mouseButtonStateEvent) override;

        std::vector<Key> m_keysDown;
        std::vector<MouseButton> m_mouseButtonsDown;

        /**
         * Current signal handler, if any
         */
        std::shared_ptr<SignalHandler> m_signalHandler;

        /**
         * Current input mapping, if any
         */
        std::shared_ptr<InputMapping> m_inputMapping;

        /**
         * List of assists.
         */
        std::vector<std::shared_ptr<Assist>> assists;
    };
}
