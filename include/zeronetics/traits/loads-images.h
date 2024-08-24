#pragma once

#include "zeronetics/core/image-data.h"
#include "zeronetics/core/io.h"

#include <optional>

namespace ZEN::Traits {
    /**
     * Trait: Loads Images
     */
    class LoadsImages {
    protected:
        /**
         * Load image from the path.
         *
         * Returns ``std::nullopt`` if the image couldn't be loaded.
         *
         * @param path
         * @return
         */
        std::optional<ImageData> loadImage(const Path &path);
    };
}
