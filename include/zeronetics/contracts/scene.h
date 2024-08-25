#pragma once

#include "zeronetics/contracts/cameras.h"
#include "zeronetics/core/io.h"
#include "renderable.h"

#include <memory>

namespace ZEN {
    /**
     * Scene Contract
     */
    class IScene {
    public:
        /**
         * 3D camera
         */
        std::shared_ptr<ICamera3D> camera3d;

        /**
         * Add a renderable to the scene.
         *
         * @param renderable
         */
        virtual void add(const std::shared_ptr<IRenderable3D> &renderable) noexcept = 0;

        /**
         * Get all renderables from the scene.
         *
         * @return
         */
        [[nodiscard]] virtual std::vector<std::shared_ptr<IRenderable3D>> getRenderable3Ds() const noexcept = 0;

    };

    /**
     * Contract: Scene Loader
     *
     * A Scene Loader translates data, such as various data interchange
     * formats (e.g. JSON, XML or HXL), into structs and classes which
     * can be consumed by Zeronetics.
     */
    class ISceneLoader {
    public:
        /**
         * Load a file and translate its data to a scene.
         *
         * @param file
         * @return
         */
        virtual std::shared_ptr<IScene> load(const File &file) = 0;
    };
}
