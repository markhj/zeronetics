#pragma once

#include "box.h"
#include "editor-utility.h"
#include "project/project.h"
#include <memory>

namespace ZenEdit {
    class BottomPanel : public EditorUtility {
    public:
        explicit BottomPanel(const std::shared_ptr<Project> &project);

        void render() override;

    private:
        Box m_box;

        std::shared_ptr<Project> m_project;

    };
}

