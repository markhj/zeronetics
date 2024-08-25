#pragma once

#include "box.h"
#include "editor-utility.h"
#include "project.h"
#include <memory>

namespace ZenEdit {
    class SidePanel : public EditorUtility {
    public:
        SidePanel(const std::shared_ptr<Project> &project);

        void render() override;

    private:
        Box m_box;

        std::shared_ptr<Project> m_project;

    };
}

