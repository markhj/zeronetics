#pragma once

#include "zeronetics/core/typedefs.h"

namespace ZEN {
    /**
     * Information about where a vertex or a set of
     * vertices have been allocated in the GPU.
     *
     * Primarily used by renderes.
     */
    struct GPUAllocation {
        gpu_alloc_int index = 0, size = 0;
    };
}
