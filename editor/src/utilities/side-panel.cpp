#include "side-panel.h"
#include "button.h"
#include "font-manager.h"
#include "label.h"
#include "separator.h"
#include <format>
#include <iostream>

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
        for (auto &scene: m_project->scenes) {
            FontManager::bold([&]() {
                Button btnOpenScene;

                if (m_project->activeScene && m_project->activeScene->name == scene.name) {
                    btnOpenScene.text = (scene.name + " *").c_str();
                } else {
                    btnOpenScene.text = scene.name.c_str();
                }

                btnOpenScene.onClick = [&]() {
                    onOpenScene(scene);
                };
                btnOpenScene.render();
            });
            Label(scene.path->getAbsolute().c_str()).render();
        }

        Button btnAddScene;
        btnAddScene.text = "Add Scene";
        btnAddScene.onClick = [&]() {
            addScene(std::format("Scene{}", m_project->scenes.size() + 1));
        };
        btnAddScene.render();

        Separator().render();

        if (!m_project->activeScene) {
            Label("No active scene.").render();
        } else {
            Label(("Scene: " + m_project->activeScene->name).c_str()).render();

            for (auto &entity: m_project->activeScene->entities) {
                Label(entity.first.c_str()).render();
            }

            Button btnAddEntity;
            btnAddEntity.text = "+ Entity";
            btnAddEntity.onClick = [&]() {
                m_project->activeScene->entities["Entity" + std::to_string(m_project->activeScene->entities.size() + 1)];
                m_project->activeScene->hasChanged = true;
            };
            btnAddEntity.render();

            Button btnSaveScene;
            btnSaveScene.text = "Save Scene";
            btnSaveScene.onClick = [&]() {
                m_project->activeScene->save();
            };
            btnSaveScene.render();

            Button btnDiscard;
            btnDiscard.text = "Discard Changes";
            btnDiscard.onClick = [&]() {
                m_project->activeScene->load();
            };
            btnDiscard.render();
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
