#pragma once

#include "ui-element.h"
#include <functional>

namespace ZenEdit {
    class Label : public UIElement {
    public:
        explicit Label(const char *setText);

        const char *text = "";

        void render() override;

    };
}
