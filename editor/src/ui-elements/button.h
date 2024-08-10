#pragma once

#include "ui-element.h"
#include <functional>

namespace ZenEdit {
    class Button : public UIElement {
    public:
        const char *text;

        std::function<void()> onClick = []() {};

        void render() override;

    };
}
