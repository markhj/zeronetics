
#pragma once

#include "scene.h"
#include "zeronetics/core/io.h"
#include <optional>
#include <string>
#include <vector>

using namespace ZEN;

namespace ZenEdit {
    class Project {
    public:
        Project();

        std::string name;

        std::vector<Scene> scenes;

        std::shared_ptr<Scene> activeScene;

        Path getPath(const char *subPath);

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
