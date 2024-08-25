#include "text-field.h"
#include "imgui.h"

void ZenEdit::TextField::render() {
    std::vector<char> buffer(value.begin(), value.end());
    buffer.resize(100);

    if (ImGui::InputText(label, buffer.data(), buffer.size())) {
        value = std::string(buffer.data());
    }
}
