#include "zeronetics/logging/log.h"
#include "zeronetics/core/sysinfo.hpp"
#include <algorithm>
#include <format>

namespace {
    const char *NO_INFO_LABEL = "-";

    struct LogMessageCooldown {
        std::string msg;
        std::chrono::time_point<std::chrono::system_clock> created;
        size_t count = 1;
    };

    std::vector<LogMessageCooldown> cooldown;

    inline std::string getTimeStamp(const char *format) {
        auto now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);
        std::tm now_tm = *std::localtime(&now_time);
        std::ostringstream strm;
        strm << std::put_time(&now_tm, format);
        return strm.str();
    }
}

double ZEN::Log::messageCooldown = 5.0;
double ZEN::Log::messageCooldownInterval = 2.0;

std::optional<ZEN::File> ZEN::Log::logFile;

std::map<ZEN::LogLevel, ZEN::LogBehavior> ZEN::Log::behaviors = {
        {ZEN::LogLevel::Info, {ZEN::LogAction::Console}},
        {ZEN::LogLevel::Warning, {ZEN::LogAction::ConsoleErr}},
        {ZEN::LogLevel::Critical, {ZEN::LogAction::Exception}},
};

std::vector<ZEN::LogCategory> ZEN::Log::blacklistCategories = {};

void ZEN::Log::message(ZEN::LogLevel level,
                       ZEN::LogCategory category,
                       std::string msg) {

    // @todo: https://github.com/markhj/zeronetics/issues/7
    //      Optimization of the code below
    if (level != LogLevel::Info) {
        bool found = false;
        auto now = std::chrono::system_clock::now();
        for (auto iter = cooldown.begin(); iter != cooldown.end();) {
            std::chrono::duration<double> elapsed = now - iter->created;

            // When the message has existed long enough on the cooldown list
            // without being invoked again, it's deleted
            if (elapsed.count() > messageCooldown) {
                iter = cooldown.erase(iter);
            } else {
                if (iter->msg == msg) {
                    found = true;
                    ++iter->count;

                    // Time between showing the message
                    if (elapsed.count() > messageCooldownInterval) {
                        msg += std::format(" [{}]", iter->count);
                        iter->created = now;
                    } else {
                        return;
                    }
                }
                ++iter;
            }
        }

        // If the message wasn't found, we add it to be observed
        // on the cooldown list.
        if (!found) {
            cooldown.emplace_back(msg, now);
        }
    }

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
        logFile = ZEN::File::loadOrCreate(
                ZEN::Path("log-" + getTimeStamp("%Y-%m-%d-%H%M") + ".txt"));
    }

    std::string str;

    if (logFileEntry.records.empty()) {
        str += std::format("[{}] {}\n\n", getTimeStamp("%H:%M:%I"), logFileEntry.message);
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

    std::string platform = NO_INFO_LABEL;
    auto platformAsString = SystemInfo::getPlatformAsString();
    if (platformAsString.has_value()) {
        platform = platformAsString.value();
    }

    std::map<std::string, std::string> records;
    records["Platform"] = platform;
    records["CPU cores"] = systemInfo.cpuCores.has_value()
                                   ? std::to_string(systemInfo.cpuCores.value())
                                   : NO_INFO_LABEL;
    records["Bitness"] = systemInfo.os.bitness.has_value()
                                 ? std::to_string(systemInfo.os.bitness.value())
                                 : NO_INFO_LABEL;

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
