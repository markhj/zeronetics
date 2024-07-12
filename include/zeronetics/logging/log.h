#pragma once

#include <string>
#include <iostream>

namespace ZEN {
    /**
     * Log category
     */
    enum class LogCategory {
        /**
         * General information, not fit for other categories.
         */
        Info,
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
        static void info(std::string_view message, LogCategory category);

        /**
         * Handle a critical message.
         *
         * These are situations which have high potential to, or certainty of,
         * causing program crashes.
         *
         * @param message
         */
        static void critical(std::string_view message);
    };
}
