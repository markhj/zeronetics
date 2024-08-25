#include "project-settings.h"
#include "box.h"

ZenEdit::ProjectSettings::ProjectSettings(bool *showBox,
                                          const std::shared_ptr<Project> &project) : m_showBox(showBox),
                                                                                     m_project(project) {
}

void ZenEdit::ProjectSettings::render() {
    Box box("Project Settings");
    box.resizable = false;
    box.collapsible = false;
    box.size = Vec2(250, 250);
    box.contains([&]() {
        TextField projectName;
        projectName.label = "Project Name";
        projectName.value = m_project->name;
        projectName.render();
    });
    box.render();
}
