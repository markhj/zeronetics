#include "font-manager.h"
#include "imgui.h"
#include <iostream>
#include <vector>

std::vector<ZenEdit::LoadedFont> ZenEdit::FontManager::s_loadedFonts;

void ZenEdit::FontManager::initialize() {
    ImGuiIO &io = ImGui::GetIO();

    struct FontFile {
        Font font;
        FontWeight fontWeight;
        const char *fontFile;
    };

    std::vector<FontFile> fontFiles = {
            {Font::Default, FontWeight::Regular, "./assets/fonts/Roboto/Roboto-Regular.ttf"},
            {Font::Default, FontWeight::Light, "./assets/fonts/Roboto/Roboto-Light.ttf"},
            {Font::Default, FontWeight::Bold, "./assets/fonts/Roboto/Roboto-Bold.ttf"},
            {Font::Default, FontWeight::Black, "./assets/fonts/Roboto/Roboto-Black.ttf"},
            {Font::Monospace, FontWeight::Regular, "./assets/fonts/IBM_Plex_Mono/IBMPlexMono-Regular.ttf"},
    };

    for (const auto &fontData: fontFiles) {
        // Note: The default size font must go first.
        for (const float &fontSize: {16.0f, 14.0f, 24.0f}) {
            ImFont *font = io.Fonts->AddFontFromFileTTF(fontData.fontFile,
                                                        fontSize,
                                                        nullptr,
                                                        io.Fonts->GetGlyphRangesDefault());
            if (font == nullptr) {
                std::cerr << "Failed to load font." << std::endl;
            }

            s_loadedFonts.emplace_back(LoadedFont{
                    .fontRequest = {
                            .fontSize = fontSize,
                            .font = fontData.font,
                            .fontWeight = fontData.fontWeight},
                    .index = io.Fonts->Fonts.size() - 1,
            });
        }
    }
}

void ZenEdit::FontManager::end() {
    ImGui::PopFont();
}

void ZenEdit::FontManager::start() {
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]);
}

void ZenEdit::FontManager::set(const ZenEdit::FontRequest &fontRequest,
                               const std::function<void()> &withFont) {
    std::optional<int> foundIndex;
    for (const LoadedFont &other: s_loadedFonts) {
        if (other.fontRequest.font == fontRequest.font && other.fontRequest.fontSize == fontRequest.fontSize && other.fontRequest.fontWeight == fontRequest.fontWeight) {
            foundIndex = other.index;
            break;
        }
    }

    if (fontRequest.textColor.has_value()) {
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(fontRequest.textColor->r,
                                                    fontRequest.textColor->g,
                                                    fontRequest.textColor->b,
                                                    1.0f));
    }

    if (foundIndex.has_value()) {
        ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[foundIndex.value()]);
        withFont();
        ImGui::PopFont();
    } else {
        std::cout << "Could not find font!" << std::endl;
        withFont();
    }

    if (fontRequest.textColor.has_value()) {
        ImGui::PopStyleColor();
    }
}
