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

ZenEdit::SidePanel::SidePanel(const std::shared_ptr<Project> &project) : m_box(Box("Side Panel")),
                                                                         m_project(project) {
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

            Button btnBack;
            btnBack.text = "<";
            btnBack.disabled = m_project->activeScene->hasChanged;
            btnBack.onClick = [&]() {
                onCloseScene();
            };
            btnBack.render();

            ImGui::SameLine();

            Button btnSaveScene;
            btnSaveScene.text = "Save";
            btnSaveScene.disabled = m_project->activeScene && m_project->activeScene->hasChanged;
            btnSaveScene.onClick = [&]() {
                m_project->activeScene->save();
            };
            btnSaveScene.render();

            ImGui::SameLine();

            Button btnDiscard;
            btnDiscard.text = "Discard";
            btnDiscard.disabled = m_project->activeScene && !m_project->activeScene->hasChanged;
            btnDiscard.onClick = [&]() {
                m_project->activeScene->load();
            };
            btnDiscard.render();

            if (m_project->activeScene) {
                for (auto &entity: m_project->activeScene->entities) {
                    Label(entity.first.c_str()).render();
                }
            }

            Button btnAddEntity;
            btnAddEntity.text = "+ Entity";
            btnAddEntity.onClick = [&]() {
                m_project->activeScene->entities["Entity" + std::to_string(m_project->activeScene->entities.size() + 1)];
                m_project->activeScene->hasChanged = true;
            };
            btnAddEntity.render();
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

            Button btnAddScene;
            btnAddScene.text = "Add Scene";
            btnAddScene.onClick = [&]() {
                addScene(std::format("Scene{}", m_project->scenes.size() + 1));
            };
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
