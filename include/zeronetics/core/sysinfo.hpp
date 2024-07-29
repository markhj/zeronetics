#pragma once

#include "enums.h"
#include <cstdint>
#include <optional>
#include <string>

namespace ZEN {
    /**
     * Details about the operating system.
     */
    struct OS {
        /**
         * Platform (e.g. Windows or Linux)
         */
        std::optional<Platform> platform;

        /**
         * Bitness (e.g. 32-bit or 64-bit)
         */
        std::optional<uint8_t> bitness;
    };

    /**
     * The compiled sheet of system information.
     */
    struct SystemInfoSheet {
        /**
         * Operating system
         */
        OS os;

        /**
         * Number of CPU cores available.
         *
         * @note If provided as ``std::nullopt`` the number of cores
         *      could not be determined.
         */
        std::optional<uint8_t> cpuCores;
    };

    class SystemInfo {
    public:
        /**
         * Get the full sheet of system information.
         * @return
         */
        static SystemInfoSheet get();

        /**
         * Get platform information (e.g. if it's Windows or Linux)
         *
         * @note If provided as ``std::nullopt`` the value could not
         *      be determined.
         *
         * @return
         */
        static std::optional<Platform> getPlatform();

        /**
         * Get system bitness (e.g. 32-bit or 64-bit)
         *
         * @note If provided as ``std::nullopt`` the value could not
         *      be determined.
         *
         * @return
         */
        static std::optional<uint8_t> getBitness();

        /**
         * Get number of CPU cores.
         *
         * @note If provided as ``std::nullopt`` the value could not
         *      be determined.
         *
         * @return
         */
        static std::optional<uint8_t> getCPUCores();

        /**
         * Get the platform as string (e.g. "Windows" or "Linux")
         *
         * @note If provided as ``std::nullopt`` the value could not
         *      be determined.
         * @return
         */
        static std::optional<std::string> getPlatformAsString();
    };
}
