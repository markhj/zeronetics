#pragma once

#include <string>
#include <vector>

#include "zeronetics/core/io.h"

using namespace ZEN;

namespace ZenEdit {
    class EditorConfig {
    public:
        EditorConfig();

        std::vector<std::string> projects;

        void load();

        void save();

    private:
        Path m_path = Path("./config.hxl");

        File m_file = File(m_path);
    };
}
