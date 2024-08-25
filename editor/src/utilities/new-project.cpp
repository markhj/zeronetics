#include "new-project.h"
#include "box.h"
#include "button.h"
#include "imgui.h"
#include "label.h"
#include "separator.h"

ZenEdit::NewProject::NewProject(bool *showBox) : m_showBox(showBox) {

}

void ZenEdit::NewProject::render() {
    Box box("New Project");
    box.contains([&]() {
        Label("Create a new project.").render();

        Button closeButton;
        closeButton.text = "Cancel";
        closeButton.onClick = [&]() { *m_showBox = false; };
        closeButton.render();
    });
    box.render();
}
