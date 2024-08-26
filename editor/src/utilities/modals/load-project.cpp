#include "load-project.h"
#include "box.h"
#include "label.h"
#include <iostream>

ZenEdit::LoadProject::LoadProject(bool *showBox) : m_showBox(showBox) {
}

void ZenEdit::LoadProject::render() {
    Box box("Load Project");
    box.resizable = false;
    box.collapsible = false;
    box.size = Vec2(500, 300);
    box.contains([&]() {
        TextField location;
        location.label = "Location";
        location.value = &m_pathToRoot;
        location.render();

        std::string error;
        if (!m_pathToRoot.empty()) {
            Path path(m_pathToRoot);
            if (!path.exists()) {
                error = "Folder does not exist.";
            } else if (!path.isDirectory()) {
                error = "Must be a directory.";
            } else if (!Path(m_pathToRoot + "/project.hxl").exists()) {
                error = "No project.hxl file found in the directory.";
            }
        }

        if (!error.empty()) {
            Label(error.c_str()).render();
        }

        Button openBtn;
        openBtn.text = "Load";
        openBtn.disabled = !error.empty();
        openBtn.onClick = [&]() { load(); };
        openBtn.render();
    });
    box.render();
}

void ZenEdit::LoadProject::load() {
    Path path(m_pathToRoot);

    m_pathToRoot.clear();
    *m_showBox = false;

    onLoad(path);
}
