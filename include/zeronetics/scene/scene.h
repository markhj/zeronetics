#pragma once

#include "zeronetics/contracts/renderable.h"
#include "zeronetics/contracts/scene.h"

#include <memory>
#include <vector>

namespace ZEN {
    /**
     * Standard implementation of a @ref ZEN::IScene "scene contract".
     */
    class Scene : public IScene {
    public:
        /**
         * Add renderable to the scene.
         *
         * @param renderable
         */
        void add(const std::shared_ptr<IRenderable3D> &renderable) noexcept override;

        /**
         * Retrieve all 3D renderables.
         *
         * @return
         */
        [[nodiscard]] std::vector<std::shared_ptr<IRenderable3D>> getRenderable3Ds() const noexcept override;

    private:
        std::vector<std::shared_ptr<IRenderable3D>> m_renderables3d;

    };
}
