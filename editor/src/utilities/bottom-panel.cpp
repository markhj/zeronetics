#include "bottom-panel.h"
#include "console.h"
#include "editor-layout.h"
#include "font-manager.h"
#include "zeronetics/core/globals.h"

ZenEdit::BottomPanel::BottomPanel(const std::shared_ptr<Project> &project) : m_project(project),
                                                                             m_box(Box("Console")) {
    m_box.movable = false;
    m_box.resizable = false;
    m_box.titleBar = false;
}

void ZenEdit::BottomPanel::render() {
    m_box.size = Vec2(Globals::viewportSize.w - EditorLayout::sidePanelWidth - EditorLayout::inspectorWidth + 2,
                      EditorLayout::bottomPanelHeight + 1);
    m_box.position = Vec2(EditorLayout::sidePanelWidth - 1,
                          Globals::viewportSize.h - EditorLayout::bottomPanelHeight);

    m_box.contains([&]() {
        Console::render();
    });
    m_box.render();
}
