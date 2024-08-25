#pragma once

#include "ui-element.h"
#include <functional>
#include <string>

namespace ZenEdit {
    class TextField : public UIElement {
    public:
        const char *label = "";

        std::string *value;

        void render() override;

    };
}
