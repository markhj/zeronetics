#include "side-panel.h"
#include "button.h"
#include "font-manager.h"
#include "label.h"
#include <format>

ZenEdit::SidePanel::SidePanel(const std::shared_ptr<Project> &project) : m_box(Box("Side Panel")),
                                                                         m_project(project) {
    m_box.resizable = false;
    m_box.collapsible = false;
    m_box.movable = false;
    m_box.titleBar = false;
    m_box.position = Vec2(5, 45);
    m_box.size = Vec2(300, 600);
}

void ZenEdit::SidePanel::render() {
    m_box.contains([&]() {
        for (const auto &scene: m_project->scenes) {
            FontManager::bold([&]() {
                Label(scene.name.c_str()).render();
            });
        }

        Button btnAddScene;
        btnAddScene.text = "Add Scene";
        btnAddScene.onClick = [&]() { m_project->scenes.emplace_back(Scene{
                                              .name = std::format("Scene{}", m_project->scenes.size() + 1)}); };
        btnAddScene.render();
    });
    m_box.render();
}
