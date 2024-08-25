#pragma once

#include "box.h"
#include "editor-utility.h"

namespace ZenEdit {
    class SidePanel : public EditorUtility {
    public:
        SidePanel();

        void render() override;

    private:
        Box m_box;

    };
}

