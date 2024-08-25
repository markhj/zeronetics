#pragma once

#include "button.h"
#include "editor-utility.h"
#include "text-field.h"
#include "zeronetics/core/io.h"
#include <regex>

using namespace ZEN;

namespace ZenEdit {
    class NewProject : public EditorUtility {
    public:
        explicit NewProject(bool *showBox);

        void render() override;

    private:
        bool *m_showBox;

        TextField m_projectName;

        TextField m_location;

        Button m_createButton;

        std::regex m_regexProjectName = std::regex(R"(^[a-zA-Z\- ]{3,}$)");

        std::optional<Path> m_basePath;

        std::optional<std::string> m_createError;

        void createProject();

        void copyStub(const Path &root, const char *file);

    };
}
