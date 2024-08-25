#pragma once

#include "ui-element.h"
#include "zeronetics/core/tensors.h"

using namespace ZEN;

namespace ZenEdit {
    class Box : public UIContainer {
    public:
        const char *text = "";

        bool resizable = true;

        bool collapsible = true;

        bool movable = true;

        bool titleBar = true;

        std::optional<Vec2> position;

        std::optional<Vec2> size;

        explicit Box(const char *setText);

    protected:
        void start() override;

        void end() override;

    };
}
