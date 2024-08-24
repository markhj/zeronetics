#include "label.h"
#include "imgui.h"

ZenEdit::Label::Label(const char *setText) : text(setText) {
}

void ZenEdit::Label::render() {
    ImGui::Text(text);
}
