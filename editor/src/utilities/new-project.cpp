#include "new-project.h"
#include "imgui.h"

ZenEdit::NewProject::NewProject(bool *showBox) : m_showBox(showBox) {

}

void ZenEdit::NewProject::render() {
    ImGui::Begin("New Project");

    ImGui::Text("Create a new project.");

    ImGui::End();
}
