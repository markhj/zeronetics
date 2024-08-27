#pragma once

#include "scene-entity.h"
#include "zeronetics/core/io.h"

#include <string>
#include <map>

using namespace ZEN;

namespace ZenEdit {
    class Scene {
    public:
        std::string name;

        std::optional<Path> path;

        std::map<std::string, SceneEntity> entities;

        void createFileIfNotExists();

        void save();

        void load();

    };
}
