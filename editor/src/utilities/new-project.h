#pragma once

#include "editor-utility.h"
#include "text-field.h"

namespace ZenEdit {
    class NewProject : public EditorUtility {
    public:
        explicit NewProject(bool *showBox);

        void render() override;

    private:
        bool *m_showBox;

        TextField m_projectName;

    };
}
