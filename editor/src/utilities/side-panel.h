#pragma once

#include "box.h"
#include "editor-utility.h"
#include "project/project.h"
#include <memory>

namespace ZenEdit {
    class SidePanel : public EditorUtility {
    public:
        explicit SidePanel(const std::shared_ptr<Project> &project);

        void render() override;

        std::function<void(Scene &scene)> onOpenScene = [&](Scene &scene) {};

        std::function<void()> onCloseScene = [&]() {};

    private:
        Box m_box;

        std::shared_ptr<Project> m_project;

        void addScene(const std::string &name);

    };
}

