
#pragma once

#include "zeronetics/core/io.h"
#include <optional>
#include <string>

using namespace ZEN;

namespace ZenEdit {
    class Project {
    public:
        Project();

        std::string name;

        void load(const Path &path);

        void reset();

        void save();

    private:
        /**
         * The path to the root of the project folder.
         */
        std::optional<Path> m_path;
    };
}
