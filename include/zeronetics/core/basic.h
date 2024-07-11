#pragma once

#include <string>
#include <cstdint>
#include <optional>

namespace ZEN {
    /**
     * Details about software version.
     */
    struct Version {
        /**
         * Preview or pre-release information.
         * For instance the "alpha.8" part of ``1.2.3-alpha.8``.
         */
        struct Preview {
            const char* label;
            uint8_t version = 1;
        };

        /**
         * Major version. The first part of ``x.y.z``.
         */
        uint8_t major = 1;

        /**
         * Minor version. The second part of ``x.y.z``.
         */
        uint8_t minor = 1;

        /**
         * Patch version. The third part of ``x.y.z``.
         */
        uint8_t patch = 0;

        /**
         * Preview/pre-release details. The part after dash
         * of ``x.y.z-label.n``.
         */
        std::optional<Preview> preview;

        /**
         * Output the version number in SemVer format.
         *
         * @return
         */
        std::string toSemVer();
    };


}
