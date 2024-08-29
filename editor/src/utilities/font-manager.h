#pragma once

#include <cstddef>
#include <functional>
#include <optional>
#include <map>
#include "zeronetics/core/attributes.h"

namespace ZenEdit {
    enum class FontWeight {
        Regular,
        Light,
        Bold,
        Black,
    };

    struct FontRequest {
        float fontSize = 16.0f;
        FontWeight fontWeight = FontWeight::Regular;
        std::optional<ZEN::ColorRGB> textColor;
    };

    struct LoadedFont {
        FontRequest fontRequest;
        std::optional<int> index;
    };

    class FontManager {
    public:
        static void initialize();

        static void end();

        static void start();

        static void set(const FontRequest &fontRequest,
                        const std::function<void()> &withFont);

    private:
        static std::vector<LoadedFont> s_loadedFonts;

        static std::optional<FontWeight> s_activeFontIndex;

    };
}
