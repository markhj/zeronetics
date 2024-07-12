#include "../include/opengl-renderer/abstracts/bindable.hpp"

template<typename T>
void OpenGL::StdBinding<T>::unbind() {
    bindTo(0);
}

template<typename T>
bool OpenGL::StdBinding<T>::isBound() const noexcept {
    return getContextId() == getCurrentContextId();
}

template<typename T>
void OpenGL::StdBinding<T>::with(const std::function<void()> &function) {
    std::optional<T> current = getCurrentContextId();
    bind();
    function();
    if (!current.has_value()) {
        unbind();
    } else if (current.value() != getContextId()) {
        bindTo(current.value());
    }
}

template<typename T>
void OpenGL::StdBinding<T>::bind() {
    bindTo(getContextId());
}
