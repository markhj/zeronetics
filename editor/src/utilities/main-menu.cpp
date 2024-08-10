#include "main-menu.h"
#include "imgui.h"

void ZenEdit::MainMenu::render() {
    if (ImGui::BeginMainMenuBar()) {
        for (const MainMenuItem &mainMenuItem: mainMenuItems) {
            if (ImGui::BeginMenu(mainMenuItem.title)) {
                for (const MainMenuItem &childItem: mainMenuItem.items) {
                    switch (childItem.type) {
                        case MainMenuType::Item:
                            if (ImGui::MenuItem(childItem.title, childItem.shortcut)) {
                                childItem.onClick();
                            }
                            break;
                        case MainMenuType::Separator:
                            ImGui::Separator();
                            break;
                    }
                }
                ImGui::EndMenu();
            }
        }
        ImGui::EndMainMenuBar();
    }
}
