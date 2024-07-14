#include "zeronetics/core/sysinfo.hpp"
#include <thread>

ZEN::SystemInfoSheet ZEN::SystemInfo::get() {
    return {
            .os = {
                    .platform = getPlatform(),
                    .bitness = getBitness(),
            },
            .cpuCores = getCPUCores(),
    };
}

std::optional<ZEN::Platform> ZEN::SystemInfo::getPlatform() {
#if defined(_WIN32) || defined(_WIN64)
                                   return Platform::Windows;
#elif defined(__APPLE__) || defined(__MACH__)
    return Platform::Mac;
#elif defined(__linux__)
    return Platform::Linux;
#else
    return std::nullopt;
#endif
}

std::optional<uint8_t> ZEN::SystemInfo::getBitness() {
#if defined(_WIN32)
    return 32;
#elif defined(_WIN64) || defined(__x86_64__) || defined(_M_X64)
    return 64;
#endif
    return std::nullopt;
}

std::optional<uint8_t> ZEN::SystemInfo::getCPUCores() {
    uint8_t cores = std::thread::hardware_concurrency();
    if (cores > 0) {
        return cores;
    }
    return std::nullopt;
}

std::optional<std::string> ZEN::SystemInfo::getPlatformAsString() {
    auto platform = getPlatform();
    if (!platform.has_value()) {
        return std::nullopt;
    }
    switch (platform.value()) {
        case Platform::Windows:
            return "Windows";
        case Platform::Linux:
            return "Linux";
        case Platform::Mac:
            return "Mac";
        default:
            return std::nullopt;
    }
}
