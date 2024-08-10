#pragma once

#include "editor-utility.h"
#include <functional>
#include <optional>
#include <vector>
namespace ZenEdit {
    enum class MainMenuType {
        Item,
        Separator,
    };

    struct MainMenuItem {
        MainMenuType type = MainMenuType::Item;
        const char *title;
        const char *shortcut;
        std::vector<MainMenuItem> items;
        std::function<void()> onClick;
    };

    class MainMenu : public EditorUtility {
    public:
        std::vector<MainMenuItem> mainMenuItems;

        void render() override;

    };
}

