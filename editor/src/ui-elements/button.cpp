#include "button.h"

#include "imgui.h"

void ZenEdit::Button::render() {
    ImVec2 size({150, 30});
    if (disabled) {
        ImGui::BeginDisabled();
        ImGui::Button(text, size);
        ImGui::EndDisabled();
    } else {
        if (ImGui::Button(text, size)) {
            onClick();
        }
    }
}
