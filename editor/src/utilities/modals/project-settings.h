#pragma once

#include "../editor-utility.h"
#include "../project/project.h"
#include "button.h"
#include "text-field.h"
#include "zeronetics/core/io.h"
#include <regex>

using namespace ZEN;

namespace ZenEdit {
    class ProjectSettings : public EditorUtility {
    public:
        ProjectSettings(bool *showBox, const std::shared_ptr<Project> &project);

        void render() override;

    private:
        bool *m_showBox;

        std::shared_ptr<Project> m_project;
    };
}
