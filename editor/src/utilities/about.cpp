#include "about.h"
#include "imgui.h"

ZenEdit::About::About(bool *showBox) : m_showBox(showBox) {
}

void ZenEdit::About::render() {
    ImGui::Begin("About");

    ImGui::Text("ZenEdit");
    ImGui::Separator();
    ImGui::Text("This is the editor for the Zeronetics game engine.");

    if (ImGui::Button("OK")) {
        *m_showBox = false;
    }

    ImGui::End();
}
