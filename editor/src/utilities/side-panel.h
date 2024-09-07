#pragma once

#include "box.h"
#include "editor-utility.h"
#include "inspector.h"
#include "project/project.h"
#include <memory>

namespace ZenEdit {
    class SidePanel : public EditorUtility {
    public:
        explicit SidePanel(const std::shared_ptr<Project> &project,
                           Inspector* inspector);

        void render() override;

        std::function<void(Scene &scene)> onOpenScene = [&](Scene &scene) {};

        std::function<void()> onCloseScene = [&]() {};

    private:
        Box m_box;

        Inspector* m_inspector;

        std::shared_ptr<Project> m_project;

        void addScene(const std::string &name);

    };
}

