#pragma once

#include "enums.h"
#include <cstdint>
#include <optional>
#include <string>

namespace ZEN {
    struct OS {
        std::optional<Platform> platform;
        std::optional<uint8_t> bitness;
    };

    struct SystemInfoSheet {
        OS os;
        std::optional<uint8_t> cpuCores;
    };

    class SystemInfo {
    public:
        static SystemInfoSheet get();

        static std::optional<Platform> getPlatform();

        static std::optional<uint8_t> getBitness();

        static std::optional<uint8_t> getCPUCores();

        static std::optional<std::string> getPlatformAsString();
    };
}
