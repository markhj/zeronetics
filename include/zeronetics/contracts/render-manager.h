
#pragma once

#include "cameras.h"
#include "renderable.h"
#include "shader.h"

#include <memory>

namespace ZEN {
    struct IRenderGroup3D {
        std::shared_ptr<IShader> shader;

        std::unordered_map<std::string, std::shared_ptr<IRenderable3D>> renderables3d;
    };

    struct IRenderManager {
        std::shared_ptr<ICamera3D> camera3d;

        std::vector<std::shared_ptr<IRenderGroup3D>> renderGroups3d;

        virtual void resetAllocations() const noexcept = 0;

    };
}

