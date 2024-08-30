#pragma once

#include "../editor-utility.h"

namespace ZenEdit {
    class ExtensionList : public EditorUtility {
    public:
        explicit ExtensionList(bool *showBox);

        void render() override;

    private:
        bool *m_showBox;

    };
}
