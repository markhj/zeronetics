#include "box.h"
#include "imgui.h"

ZenEdit::Box::Box(const char *setText) : text(setText) {
}

void ZenEdit::Box::start() {
    ImGui::Begin(text);
}

void ZenEdit::Box::end() {
    ImGui::End();
}
