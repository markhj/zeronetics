#pragma once

#include "ui-element.h"
#include <functional>

namespace ZenEdit {
    class Button : public UIElement {
    public:
        const char *text;

        bool disabled = false;

        std::function<void()> onClick = []() {};

        void render() override;

    };
}
