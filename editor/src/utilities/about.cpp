#include "about.h"
#include "../editor-ui.h"
#include "../ui-elements/button.h"
#include "imgui.h"

ZenEdit::About::About(bool *showBox) : m_showBox(showBox) {
}

void ZenEdit::About::render() {
    ImGui::Begin("About");

    ImGui::Text("ZenEdit");
    ImGui::Separator();
    ImGui::Text("This is the editor for the Zeronetics game engine.");

    Button okButton;
    okButton.text = "OK";
    okButton.onClick = [&]() { *m_showBox = false; };
    okButton.render();

    ImGui::End();
}
