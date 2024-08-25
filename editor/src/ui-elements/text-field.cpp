#include "text-field.h"
#include "imgui.h"
#include <iostream>

void ZenEdit::TextField::render() {
    if (value == nullptr) {
        std::cerr << "A text field has not been assigned a value." << std::endl;
        return;
    }

    std::vector<char> buffer(value->begin(), value->end());
    buffer.resize(100);

    if (ImGui::InputText(label, buffer.data(), buffer.size())) {
        *value = std::string(buffer.data());
    }
}
