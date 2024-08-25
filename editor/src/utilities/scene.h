#pragma once

#include "scene-entity.h"

#include <string>
#include <unordered_map>

namespace ZenEdit {
    class Scene {
    public:
        std::string name;

        std::unordered_map<const char *, SceneEntity> entities;
    };
}
