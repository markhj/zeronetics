#pragma once

#include "button.h"
#include "editor-utility.h"
#include "project.h"
#include "text-field.h"
#include "zeronetics/core/io.h"
#include <regex>

using namespace ZEN;

namespace ZenEdit {
    class LoadProject : public EditorUtility {
    public:
        explicit LoadProject(bool *showBox);

        void render() override;

        std::function<void(const Path &path)> onLoad = [](const Path &path) {};

    private:
        bool *m_showBox;

        std::string m_pathToRoot;

        void load();

    };
}
