#pragma once

#include "zeronetics/core/io.h"
#include "renderable.h"

#include <memory>

namespace ZEN {
    class IScene {
    public:
        virtual void add(const std::shared_ptr<IRenderable3D> &renderable) noexcept = 0;

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
