
#pragma once

#include "shader.h"
#include "cameras.h"

#include <memory>

namespace ZEN {
    class IRenderManager {
    public:
        std::shared_ptr<ICamera3D> camera3d;

        std::unordered_map<std::string_view, std::shared_ptr<IShader>> shaders;

    };
}

