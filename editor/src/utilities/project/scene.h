#pragma once

#include "scene-entity.h"
#include "zeronetics/core/io.h"

#include <string>
#include <unordered_map>

using namespace ZEN;

namespace ZenEdit {
    class Scene {
    public:
        std::string name;

        std::optional<Path> path;

        std::unordered_map<std::string, SceneEntity> entities;

        void createFileIfNotExists();

        void save();

        void load();

    };
}
