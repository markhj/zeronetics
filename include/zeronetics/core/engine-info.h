#pragma once

#include <string>

#include "zeronetics/core/version.h"

namespace ZEN {
    /**
     * Retrieve information about the engine.
     */
    struct EngineInfo {
        /**
         * Get current engine version.
         *
         * @return
         */
        static Version getVersion();

    };
}

