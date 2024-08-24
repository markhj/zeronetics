#pragma once

#include <functional>
#include <optional>

namespace ZenEdit {
    class UIElement {
    public:
        virtual void render() = 0;

    };

    class UIContainer : public UIElement {
    public:
        void contains(const std::function<void()> &func);

        void render() final;

    protected:
        virtual void start() = 0;

        virtual void end() = 0;

    private:
        std::optional<std::function<void()>> m_contains;

    };
}

