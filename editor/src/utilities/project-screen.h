#pragma once

#include "button.h"
#include "editor-config.h"
#include "editor-utility.h"
#include "project.h"
#include "text-field.h"
#include "zeronetics/core/io.h"
#include <regex>

using namespace ZEN;

namespace ZenEdit {
    class ProjectScreen : public EditorUtility {
    public:
        ProjectScreen(EditorConfig *editorConfig,
                      bool *showNewProject,
                      bool *showLoadProject);

        void render() override;

        std::function<void(const std::string &)> onOpenProject = [&](const std::string &path) {};

    private:
        EditorConfig *m_editorConfig;

        bool *m_showNewProject, *m_showLoadProject;
    };
}
