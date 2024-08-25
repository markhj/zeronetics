#include "box.h"
#include "imgui.h"

ZenEdit::Box::Box(const char *setText) : text(setText) {
}

void ZenEdit::Box::start() {
    ImGuiWindowFlags flags = 0;

    if (!resizable) {
        flags |= ImGuiWindowFlags_NoResize;
    }

    if (!movable) {
        flags |= ImGuiWindowFlags_NoMove;
    }

    if (!collapsible) {
        flags |= ImGuiWindowFlags_NoCollapse;
    }

    if (!titleBar) {
        flags |= ImGuiWindowFlags_NoDecoration;
    }

    if (size.has_value()) {
        ImGui::SetNextWindowSize(ImVec2(size->x, size->y));
    }

    if (position.has_value()) {
        ImGui::SetNextWindowPos(ImVec2(position->x, position->y));
    }

    ImGui::Begin(text, nullptr, flags);
}

void ZenEdit::Box::end() {
    ImGui::End();
}
