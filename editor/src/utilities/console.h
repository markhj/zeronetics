#pragma once

#include <string>
#include <vector>

namespace ZenEdit {
    enum class ConsoleMessageType {
        Info,
        Error,
        Warning,
        Success,
    };

    struct ConsoleMessage {
        ConsoleMessageType type = ConsoleMessageType::Info;
        std::string text;
    };

    class Console {
    public:
        static std::vector<ConsoleMessage> messages;

        static void render();

        static void info(const std::string &text);

        static void error(const std::string &text);

        static void warn(const std::string &text);
    };
}
