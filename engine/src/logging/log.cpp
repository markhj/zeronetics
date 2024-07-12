#include "zeronetics/logging/log.h"

void ZEN::Log::info(std::string_view message, ZEN::LogCategory category) {
    std::cout << "LOG: " << message << std::endl;
}

void ZEN::Log::critical(std::string_view message) {
    std::cerr << message << std::endl;
}
