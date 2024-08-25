#include "side-panel.h"

ZenEdit::SidePanel::SidePanel() : m_box(Box("Side Panel")) {
    m_box.resizable = false;
    m_box.collapsible = false;
    m_box.movable = false;
    m_box.titleBar = false;
    m_box.position = Vec2(5, 45);
    m_box.size = Vec2(300, 600);
}

void ZenEdit::SidePanel::render() {
    m_box.render();
}
