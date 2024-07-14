#include "zeronetics/logging/log.h"
#include "zeronetics/core/sysinfo.hpp"
#include <algorithm>
#include <format>

std::optional<ZEN::File> ZEN::Log::logFile;

std::map<ZEN::LogLevel, ZEN::LogBehavior> ZEN::Log::behaviors = {
        {ZEN::LogLevel::Info, {ZEN::LogAction::Console}},
        {ZEN::LogLevel::Warning, {ZEN::LogAction::ConsoleErr}},
        {ZEN::LogLevel::Critical, {ZEN::LogAction::Exception}},
};

std::vector<ZEN::LogCategory> ZEN::Log::blacklistCategories = {};

void ZEN::Log::message(ZEN::LogLevel level,
                       ZEN::LogCategory category,
                       const std::string &msg) {
    switch (behaviors[level].takeAction) {
        case LogAction::Silent:
            break;
        case LogAction::Console:
            std::cout << msg << std::endl;
            break;
        case LogAction::ConsoleErr:
            std::cerr << msg << std::endl;
            break;
        case LogAction::Exception:
            throw std::runtime_error(msg);
    }
}

void ZEN::Log::info(const std::string &msg, ZEN::LogCategory category) {
    logToFileIfCategory(category, {
                                          .message = msg,
                                  });
    message(LogLevel::Info, category, msg);
}

void ZEN::Log::warn(const std::string &msg, ZEN::LogCategory category) {
    logToFileIfCategory(category, {
                                          .message = std::format("CRITICAL: {}", msg),
                                  });
    message(LogLevel::Warning, category, msg);
}

void ZEN::Log::critical(const std::string &msg) {
    // @note: Critical level is always logged to file
    logToFile({
            .message = std::format("WARNING: {}", msg),
    });
    message(LogLevel::Critical, LogCategory::Critical, msg);
}

void ZEN::Log::report(const ZEN::LogFileEntry &logFileEntry) {
    logToFile(logFileEntry);
}

void ZEN::Log::logToFile(const ZEN::LogFileEntry &logFileEntry) {
    if (!logFile.has_value()) {
        auto now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);
        std::tm now_tm = *std::localtime(&now_time);
        std::ostringstream strm;
        strm << std::put_time(&now_tm, "%Y-%m-%d-%H%M");
        logFile = ZEN::File::loadOrCreate(ZEN::Path("log-" + strm.str() + ".txt"));
    }

    std::string str;

    if (logFileEntry.records.empty()) {
        auto now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);
        std::tm now_tm = *std::localtime(&now_time);
        std::ostringstream strm;
        strm << std::put_time(&now_tm, "%H:%M:%I");

        str += std::format("[{}] {}\n\n", strm.str(), logFileEntry.message);
    } else {
        str += std::format("[{}]\n", logFileEntry.message);
        for (const auto &item: logFileEntry.records) {
            str += std::format("\t{}: {}\n", item.first, item.second);
        }
        str += "\n";
    }

    logFile->append(str);
}

void ZEN::Log::startReporting() {
    SystemInfoSheet systemInfo = SystemInfo::get();

    std::string platform = "Unknown";
    auto platformAsString = SystemInfo::getPlatformAsString();
    if (platformAsString.has_value()) {
        platform = platformAsString.value();
    }

    std::map<std::string, std::string> records;
    records["Platform"] = platform;

    if (systemInfo.cpuCores.has_value()) {
        records["CPU cores"] = std::to_string(systemInfo.cpuCores.value());
    }

    if (systemInfo.os.bitness.has_value()) {
        records["Bitness"] = std::to_string(systemInfo.os.bitness.value());
    }

    report({"System Information", records});
}

void ZEN::Log::logToFileIfCategory(ZEN::LogCategory category,
                                   const ZEN::LogFileEntry &logFileEntry) {
    auto it = std::find_if(blacklistCategories.begin(),
                           blacklistCategories.end(),
                           [&](const LogCategory &other) -> bool {
                               return other == category;
                           });

    if (it == blacklistCategories.end()) {
        logToFile(logFileEntry);
    }
}
