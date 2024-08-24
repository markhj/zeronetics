#pragma once

#include "ui-element.h"

namespace ZenEdit {
    class Box : public UIContainer {
    public:
        const char *text = "";

        explicit Box(const char *setText);

    protected:
        void start() override;

        void end() override;

    };
}
