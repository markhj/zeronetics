#pragma once

#include <string>

#include "zeronetics/core/version.h"

namespace ZEN {
    /**
     * Retrieve information about the engine.
     */
    class EngineInfo {
    public:
        /**
         * Get current engine version.
         *
         * @return
         */
        static Version getVersion();

    };
}

