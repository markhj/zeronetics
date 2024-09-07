#pragma once

#include "box.h"
#include "editor-utility.h"
#include "project/project.h"
#include <memory>

namespace ZenEdit {
    class Inspector : public EditorUtility {
    public:
        explicit Inspector(const std::shared_ptr<Project> &project);

        void open(SceneEntity *entity);

        void render() override;

    private:
        Box m_box;

        SceneEntity *m_entity = nullptr;

        std::shared_ptr<Project> m_project;
    };
}
