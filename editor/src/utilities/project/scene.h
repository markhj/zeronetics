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

        std::unordered_map<const char *, SceneEntity> entities;

        void save();

        void load();

    };
}
