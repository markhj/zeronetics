#pragma once

#include <iostream>
#include <map>
#include <string>

#include "zeronetics/core/io.h"

namespace ZEN {
    /**
     * Log category
     */
    enum class LogCategory {
        /**
         * General information, not fit for other categories.
         */
        Info,

        /**
         * Rendering or renderer related information.
         */
        RendererInit,
        Rendering,
        RendererInternals,

        ShaderCompilation,
        ShaderUse,
    };

    struct LogFileEntry {
        std::string message;
        std::map<std::string, std::string> records;
    };

    /**
     * Log
     *
     * @ref logging
     */
    class Log {
    public:
        /**
         * Print a general info-level message
         *
         * @param message
         * @param category
         */
        static void info(const std::string &message, LogCategory category);

        /**
         * Print warning-level information.
         *
         * @param message
         * @param category
         */
        static void warn(const std::string &message, LogCategory category);

        /**
         * Handle a critical message.
         *
         * These are situations which have high potential to, or certainty of,
         * causing program crashes.
         *
         * @param message
         */
        static void critical(const std::string &message);

        /**
         * A report-level message is one that regardless of build mode is added
         * to the log file.
         *
         * The level is intended for information which is beneficial when analyzing
         * what happened on another machine, such as a user's*
         *
         * *) Remember to acquire consent before collecting and sending log information.
         */
        static void report(const LogFileEntry &logFileEntry);

        /**
         * Initialize basic reporting
         */
        static void startReporting();

    private:
        static void logToFile(const LogFileEntry &logFileEntry);

        static std::optional<File> logFile;
    };
}
