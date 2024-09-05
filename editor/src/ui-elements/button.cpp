#include "button.h"

#include "imgui.h"

ZenEdit::Button::Button(const char *setText,
                        const std::function<void()> &setOnClick) : text(setText),
                                                                   onClick(setOnClick) {
}

ZenEdit::Button::Button() : text("") {
}

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
