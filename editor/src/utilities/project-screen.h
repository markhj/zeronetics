#pragma once

#include "button.h"
#include "editor-utility.h"
#include "project.h"
#include "text-field.h"
#include "zeronetics/core/io.h"
#include <regex>

using namespace ZEN;

namespace ZenEdit {
    class ProjectScreen : public EditorUtility {
    public:
        ProjectScreen(bool *showNewProject, bool *showLoadProject);

        void render() override;

    private:
        bool *m_showNewProject, *m_showLoadProject;
    };
}
