#pragma once

#include "zeronetics/contracts/scene.h"
#include "zeronetics/core/io.h"

#include <memory>

namespace ZEN {
    /**
     * Scene Loader (HXL) loads scene data written in the HXL
     * data interchange format.
     *
     * @see https://github.com/markhj/hxl-lang
     */
    class SceneLoaderHxl : public ISceneLoader {
    public:
        /**
         * Create new HXL Scene Loader.
         */
        SceneLoaderHxl();

        /**
         * Load data from a specific file and translate it into a scene object.
         *
         * @param file
         * @return
         */
        std::shared_ptr<IScene> load(const File &file) override;

    };
}
