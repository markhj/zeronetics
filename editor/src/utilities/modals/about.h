#pragma once

#include "../editor-utility.h"

namespace ZenEdit {
    class About : public EditorUtility {
    public:
        explicit About(bool *showBox);

        void render() override;

    private:
        bool *m_showBox;

    };
}
