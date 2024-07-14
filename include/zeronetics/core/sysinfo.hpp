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
        SystemInfoSheet get();

        std::optional<Platform> getPlatform();

        std::optional<uint8_t> getBitness();

        std::optional<uint8_t> getCPUCores();

        std::optional<std::string> getPlatformAsString();
    };
}
