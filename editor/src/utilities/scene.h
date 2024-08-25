#pragma once

#include "scene-entity.h"

#include <unordered_map>

namespace ZenEdit {
    class Scene {
    public:
        std::unordered_map<const char *, SceneEntity> entities;
    };
}
