#pragma once

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "zeronetics/core/io.h"

namespace ZEN {
    /**
     * Log level (severity)
     *
     * @ref log-configuration
     */
    enum class LogLevel {
        Info,
        Warning,
        Critical,
    };

    /**
     * Log category
     *
     * @ref log-configuration
     */
    enum class LogCategory {
        None,

        Critical,

        /**
         * General information, not fit for other categories.
         */
        Info,

        /**
         * Errors related to the file system, such as loading files
         */
        FileSystem,

        /**
         * Rendering or renderer related information.
         */
        RendererInit,
        Rendering,
        RendererInternals,

        ShaderCompilation,
        ShaderUse,

        /**
         * User inputs, mapping, handling of controls, etc.
         */
        Controls,

        /**
         * Related to the management and life-cycle of processes.
         */
        Process,
    };

    /**
     * The look of a log entry which is put into
     * the active log file.
     *
     * @ref log-reporting
     */
    struct LogFileEntry {
        std::string message;
        std::map<std::string, std::string> records;
    };

    /**
     * Action to be taken when a log level is invoked.
     *
     * @ref log-configuration
     */
    enum class LogAction {
        Silent,
        Console,
        ConsoleErr,
        Exception,
    };

    /**
     * Struct for decision-making on log level behavior
     *
     * @ref log-configuration
     */
    struct LogBehavior {
        LogAction takeAction = LogAction::Console;
    };

    /**
     * Log
     *
     * @ref logging
     */
    class Log {
    public:
        /**
         * Definitions of each log level's behavior
         *
         * @ref log-configuration
         */
        static std::map<LogLevel, LogBehavior> behaviors;

        /**
         * Categories that should not be handled.
         *
         * @ref log-configuration
         */
        static std::vector<LogCategory> blacklistCategories;

        /**
         * The minimum interval between logging identical messages,
         * and until it's possible again.
         *
         * This only concerns critical and warning level messages.
         * Info level can be posted at any frequency.
         */
        static double messageCooldown;

        /**
         * The time between identical messages being posted, and until
         * they will appear again, this time with a count of how many
         * times the message attempted to appear in this interval.
         */
        static double messageCooldownInterval;

        /**
         * General log message functionality.
         *
         * @param level
         * @param category
         * @param message
         */
        static void message(LogLevel level,
                            LogCategory category,
                            std::string message);

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
         *
         * @ref log-reporting
         */
        static void report(const LogFileEntry &logFileEntry);

        /**
         * Initialize basic reporting
         *
         * @ref log-reporting
         */
        static void startReporting();

    private:
        static void logToFile(const LogFileEntry &logFileEntry);

        static void logToFileIfCategory(LogCategory category,
                                        const LogFileEntry &logFileEntry);



        static std::optional<File> logFile;
    };
}
