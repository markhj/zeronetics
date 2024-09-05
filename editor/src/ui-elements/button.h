#pragma once

#include "ui-element.h"
#include <functional>

namespace ZenEdit {
    class Button : public UIElement {
    public:
        Button();

        Button(const char *setText, const std::function<void()> &setOnClick);

        const char *text;

        bool disabled = false;

        std::function<void()> onClick = []() {};

        void render() override;

    };
}
