#pragma once

#include "zeronetics/core/image-data.h"
#include "zeronetics/core/io.h"

#include <optional>

namespace ZEN::Traits {
    class LoadsImages {
    protected:
        std::optional<ImageData> loadImage(const Path &path);
    };
}
