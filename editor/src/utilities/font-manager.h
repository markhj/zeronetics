#pragma once

#include <cstddef>
#include <functional>
#include <optional>

namespace ZenEdit {
    enum class FontSelection {
        Regular,
        Light,
        Bold,
        Black,
    };

    class FontManager {
    public:
        static void initialize();

        static void end();

        static void start();

        static void bold(const std::function<void()> &withFont);

        static void light(const std::function<void()> &withFont);

        static void black(const std::function<void()> &withFont);

    private:
        static inline void setFont(const std::function<void()> &withFont, int index);

        static std::optional<FontSelection> s_activeFontIndex;

    };
}
