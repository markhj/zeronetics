#pragma once

#include "zeronetics/core/enums.h"

namespace ZEN {
    /**
     * Container for values which must be quickly accessible from
     * everywhere in the code.
     */
    struct Globals {
        /**
         * The size of the viewport (typically the window, or even screen size).
         */
        static ViewportSize viewportSize;
    };
}
