#pragma once

#include "ui-elements/ui-element.h"
#include <functional>
#include <memory>

namespace ZenEdit {
    struct Container {
        const char *title;
        std::vector<std::shared_ptr<UIElement>> elements;
    };

    class EditorUI {
    public:
        std::vector<Container *> containers;

        void render();
    };
}
