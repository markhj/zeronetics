#include "inspector.h"
#include "editor-layout.h"
#include "zeronetics/core/globals.h"

void ZenEdit::Inspector::render() {
    m_box.size = Vec2(EditorLayout::inspectorWidth, Globals::viewportSize.h);
    m_box.position = Vec2(Globals::viewportSize.w - EditorLayout::inspectorWidth,
                          EditorLayout::sidePanelPosY);
    m_box.render();
}

ZenEdit::Inspector::Inspector(const std::shared_ptr<Project> &project) : m_project(project),
                                                                         m_box(Box("Inspector")) {
    m_box.titleBar = false;
    m_box.resizable = false;
    m_box.movable = false;
}
