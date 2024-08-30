#include "button.h"

#include "imgui.h"

void ZenEdit::Button::render() {
    if (disabled) {
        ImGui::BeginDisabled();
    }

    if (ImGui::Button(text)) {
        onClick();
    }

    if (disabled) {
        ImGui::EndDisabled();
    }
}
