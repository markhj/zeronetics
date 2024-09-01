#pragma once

#include "../editor-utility.h"
#include <functional>
#include <string>

namespace ZenEdit {
    class ExtensionList : public EditorUtility {
    public:
        explicit ExtensionList(bool *showBox);

        void render() override;

        std::function<void(const std::string &entityName)> onCreateEntity = [&](const std::string &entityName) {};

    private:
        bool *m_showBox;

    };
}
