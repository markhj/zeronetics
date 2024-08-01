#pragma once

#include <functional>
#include <memory>

namespace ZenEdit {
    struct UIElement {
        virtual void render() = 0;
    };

    struct Container {
        const char *title;
        std::vector<std::shared_ptr<UIElement>> elements;
    };

    struct Button : public UIElement {
        const char *text;
        std::function<void()> onClick = [](){};

        void render() override;
    };

    class EditorUI {
    public:
        std::vector<Container *> containers;

        void render();
    };
}
