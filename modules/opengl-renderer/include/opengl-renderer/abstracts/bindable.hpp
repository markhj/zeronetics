#pragma once

#include <functional>
#include <optional>

namespace ZEN::OpenGL {
    /**
     * Contract for OpenGL context binding.
     *
     * @tparam T
     */
    template<typename T>
    class IBindable {
    public:
        virtual void bindTo(T context) = 0;

        virtual void unbind() = 0;

        [[nodiscard]] virtual T getContextId() const = 0;

        virtual void bind() = 0;

        virtual void with(const std::function<void()> &function) = 0;

        [[nodiscard]] virtual bool isBound() const noexcept = 0;

    protected:
        [[nodiscard]] virtual std::optional<T> getCurrentContextId() const = 0;
    };

    /**
     * Abstract class which implements as much as possible of the
     * OpenGL::IBindable contract, by leaves context-specific implementation open.
     *
     * @ref opengl-bindable
     */
    template<typename T>
    class StdBinding : public IBindable<T> {
    public:
        void bindTo(T context) override = 0;

        void unbind() override;

        [[nodiscard]] T getContextId() const override = 0;

        void bind() override;

        void with(const std::function<void()> &function) override;

        [[nodiscard]] bool isBound() const noexcept override;

    protected:
        [[nodiscard]] std::optional<T> getCurrentContextId() const override = 0;
    };
}

