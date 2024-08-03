#pragma once

#include "zeronetics/core/typedefs.h"

namespace ZEN {
    /**
     * Information about where a vertex or a set of
     * vertices have been allocated in the GPU.
     *
     * Primarily used by renderers.
     */
    struct GPUAllocation {
        /**
         * The position of the allocation.
         */
        gpu_alloc_int index = 0;

        /**
         * Size of allocation.
         */
        gpu_alloc_int size = 0;
    };
}
