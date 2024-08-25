#include "button.h"

#include "imgui.h"

void ZenEdit::Button::render() {
    if (ImGui::Button(text, {150, 30})) {
        onClick();
    }
}
