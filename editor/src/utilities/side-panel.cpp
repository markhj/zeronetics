#include "side-panel.h"
#include "button.h"
#include "editor-layout.h"
#include "font-manager.h"
#include "imgui.h"
#include "label.h"
#include "separator.h"
#include "zeronetics/core/globals.h"
#include <format>
#include <iostream>

ZenEdit::SidePanel::SidePanel(const std::shared_ptr<Project> &project,
                              Inspector *inspector) : m_box(Box("Side Panel")),
                                                      m_project(project),
                                                      m_inspector(inspector) {
    m_box.resizable = false;
    m_box.collapsible = false;
    m_box.movable = false;
    m_box.titleBar = false;
    m_box.position = Vec2(0, EditorLayout::sidePanelPosY);
}

void ZenEdit::SidePanel::render() {
    // Size must be set here to account for resizing during runtime
    m_box.size = Vec2(EditorLayout::sidePanelWidth, Globals::viewportSize.h);

    m_box.contains([&]() {
        if (m_project->activeScene) {
            FontManager::set({
                                     .fontSize = 24.0f,
                                     .fontWeight = FontWeight::Bold,
                             },
                             [&]() {
                                 Label(m_project->activeScene->name.c_str()).render();
                             });

            Separator().render();

            Button btnBack("<", [&]() { onCloseScene(); });
            btnBack.disabled = m_project->activeScene->hasChanged;
            btnBack.render();

            ImGui::SameLine();

            Button btnSaveScene("Save", [&]() { m_project->activeScene->save(); });
            btnSaveScene.disabled = m_project->activeScene && !m_project->activeScene->hasChanged;
            btnSaveScene.render();

            ImGui::SameLine();

            Button btnDiscard("Discard", [&]() { m_project->activeScene->load(); });
            btnDiscard.disabled = m_project->activeScene && !m_project->activeScene->hasChanged;
            btnDiscard.render();

            if (m_project->activeScene) {
                for (auto &entity: m_project->activeScene->entities) {
                    Button(entity.first.c_str(), [&]() {
                        m_inspector->open(&entity.second);
                    }).render();
                }
            }
        } else {
            for (auto &scene: m_project->scenes) {
                FontManager::set({}, [&]() {
                    Button btnOpenScene;
                    btnOpenScene.text = scene.name.c_str();
                    btnOpenScene.onClick = [&]() {
                        onOpenScene(scene);
                    };
                    btnOpenScene.render();
                });
            }

            Button btnAddScene("Add Scene", [&]() {
                addScene(std::format("Scene{}", m_project->scenes.size() + 1));
            });
            btnAddScene.render();
        }
    });
    m_box.render();
}

void ZenEdit::SidePanel::addScene(const std::string &name) {
    Scene scene;
    scene.name = name;
    scene.path = m_project->getPath((m_project->hxlDataDir + "/" + name + ".hxl").c_str());

    m_project->scenes.emplace_back(scene);
}
