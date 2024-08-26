#include "project-screen.h"
#include "box.h"
#include "label.h"

#include "separator.h"
#include "zeronetics/core/globals.h"

ZenEdit::ProjectScreen::ProjectScreen(EditorConfig *editorConfig,
                                      bool *showNewProject,
                                      bool *showLoadProject) : m_editorConfig(editorConfig),
                                                               m_showNewProject(showNewProject),
                                                               m_showLoadProject(showLoadProject) {
}

void ZenEdit::ProjectScreen::render() {
    Box box("Projects");
    box.resizable = false;
    box.movable = false;
    box.collapsible = false;
    box.size = Vec2(500, 400);
    box.position = Vec2(Globals::viewportSize.w / 2.0 - box.size->x / 2.0, 50);
    box.contains([&]() {
        Button btnCreate;
        btnCreate.text = "New Project...";
        btnCreate.onClick = [&]() { *m_showNewProject = true; };
        btnCreate.render();

        Button btnLoad;
        btnLoad.text = "Load...";
        btnLoad.onClick = [&]() { *m_showLoadProject = true; };
        btnLoad.render();

        Separator().render();

        for (const auto &projectPath: m_editorConfig->projects) {
            Button btnOpenProject;
            btnOpenProject.text = projectPath.c_str();
            btnOpenProject.onClick = [&]() { onOpenProject(projectPath); };
            btnOpenProject.render();
        }
    });

    box.render();
}
