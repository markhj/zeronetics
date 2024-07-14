
#pragma once

#include "cameras.h"
#include "renderable.h"
#include "shader.h"

#include <memory>

namespace ZEN {
    struct IRendererRequest {
        RenderManagerRequest request;
    };

    struct IRenderGroup3D {
        std::shared_ptr<IShader> shader;

        std::unordered_map<std::string, std::shared_ptr<IRenderable3D>> renderables3d;
    };

    /**
     * A Render Manager is a way for "something" and a renderer
     * to communicate, without introducing coupling between that "something"
     * and the renderer. The "something" is typically some sort
     * of scene-related object, but it doesn't have to be.
     *
     * They have different authorities over the render manager, and can
     * both update its data. For instance, a scene-like object can
     * place requests, and the renderer can remove them, when they are
     * processed.
     */
    struct IRenderManager {
        std::shared_ptr<ICamera3D> camera3d;

        std::vector<std::shared_ptr<IRenderGroup3D>> renderGroups3d;

        std::vector<std::unique_ptr<IRendererRequest>> requests;

        virtual void resetAllocations() const noexcept = 0;

    };
}

