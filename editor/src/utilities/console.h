#pragma once

#include <string>
#include <vector>

namespace ZenEdit {
    struct ConsoleMessage {
        std::string text;
    };

    class Console {
    public:
        static std::vector<ConsoleMessage> messages;

        static void add(const std::string &text);
    };
}
