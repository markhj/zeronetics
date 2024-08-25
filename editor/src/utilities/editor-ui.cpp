#include "editor-ui.h"
#include "imgui.h"


void ZenEdit::EditorUI::render() {
    ImGuiIO &io = ImGui::GetIO();

    std::for_each(containers.begin(), containers.end(), [&](const Container *item) {
        ImGui::Begin(item->title);
        std::for_each(item->elements.begin(), item->elements.end(), [&](const std::shared_ptr<UIElement> &item) {
            item->render();
        });
        ImGui::End();
    });
}
