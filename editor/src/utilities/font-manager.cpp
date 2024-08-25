#include "font-manager.h"
#include "imgui.h"
#include <iostream>
#include <vector>

std::optional<ZenEdit::FontSelection> ZenEdit::FontManager::s_activeFontIndex;

void ZenEdit::FontManager::initialize() {
    ImGuiIO &io = ImGui::GetIO();
    float fontSize = 16.0f;

    std::vector<const char *> fontFiles = {
            "./assets/fonts/Roboto/Roboto-Regular.ttf",
            "./assets/fonts/Roboto/Roboto-Light.ttf",
            "./assets/fonts/Roboto/Roboto-Bold.ttf",
            "./assets/fonts/Roboto/Roboto-Black.ttf",
    };

    for (const auto &path: fontFiles) {
        ImFont* font = io.Fonts->AddFontFromFileTTF(path, fontSize, nullptr, io.Fonts->GetGlyphRangesDefault());
        if (font == nullptr) {
            std::cerr << "Failed to load font." << std::endl;
        }
    }
}

void ZenEdit::FontManager::end() {
    ImGui::PopFont();
}

void ZenEdit::FontManager::start() {
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]);
}

void ZenEdit::FontManager::light(const std::function<void()> &withFont) {
    setFont(withFont, 1);
}

void ZenEdit::FontManager::bold(const std::function<void()> &withFont) {
    setFont(withFont, 2);
}

void ZenEdit::FontManager::black(const std::function<void()> &withFont) {
    setFont(withFont, 3);
}

void ZenEdit::FontManager::setFont(const std::function<void()> &withFont, int index) {
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[index]);
    withFont();
    ImGui::PopFont();
}
