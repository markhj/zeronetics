#include "project-settings.h"
#include "box.h"
#include <iostream>

ZenEdit::ProjectSettings::ProjectSettings(bool *showBox,
                                          const std::shared_ptr<Project> &project) : m_showBox(showBox),
                                                                                     m_project(project) {
}

void ZenEdit::ProjectSettings::render() {
    Box box("Project Settings");
    box.resizable = false;
    box.collapsible = false;
    box.size = Vec2(500, 150);

    box.contains([&]() {
        TextField projectName;
        projectName.label = "Project Name";
        projectName.value = &m_project->name;
        projectName.render();

        Button closeBtn;
        closeBtn.text = "OK";
        closeBtn.onClick = [&]() { *m_showBox = false; };
        closeBtn.render();
    });
    box.render();
}
