#include "inspector.h"
#include "editor-layout.h"
#include "label.h"
#include "zeronetics/core/globals.h"

ZenEdit::Inspector::Inspector(const std::shared_ptr<Project> &project) : m_project(project),
                                                                         m_box(Box("Inspector")) {
    m_box.titleBar = false;
    m_box.resizable = false;
    m_box.movable = false;
}

void ZenEdit::Inspector::open(SceneEntity *entity) {
    m_entity = entity;
}

void ZenEdit::Inspector::render() {
    m_box.size = Vec2(EditorLayout::inspectorWidth, Globals::viewportSize.h);
    m_box.position = Vec2(Globals::viewportSize.w - EditorLayout::inspectorWidth,
                          EditorLayout::sidePanelPosY);

    m_box.contains([&]() {
        if (m_entity) {
            Label(m_entity->type.c_str()).render();
            Label(m_entity->name.c_str()).render();
        }
    });

    m_box.render();
}
