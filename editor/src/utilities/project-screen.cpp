#include "project-screen.h"
#include "box.h"
#include "label.h"

#include "zeronetics/core/globals.h"

ZenEdit::ProjectScreen::ProjectScreen(bool *showNewProject, bool *showLoadProject) : m_showNewProject(showNewProject),
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
    });
    box.render();
}
