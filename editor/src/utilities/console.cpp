#include "console.h"
#include "font-manager.h"
#include "label.h"

namespace {
    ZEN::ColorRGB typeToColor(const ZenEdit::ConsoleMessageType &type) {
        switch (type) {
            case ZenEdit::ConsoleMessageType::Error:
                return {1.0f, 0.0f, 0.0f};
            case ZenEdit::ConsoleMessageType::Warning:
                return {1.0f, 1.0f, 0.0f};
            case ZenEdit::ConsoleMessageType::Success:
                return {0.5f, 0.8f, 0.05f};
            default:
                return {1.0f, 1.0f, 1.0f};
        }
    }
}

std::vector<ZenEdit::ConsoleMessage> ZenEdit::Console::messages;

void ZenEdit::Console::info(const std::string &text) {
    messages.emplace_back(ConsoleMessage{.text = text});
}

void ZenEdit::Console::error(const std::string &text) {
    messages.emplace_back(ConsoleMessage{
            .type = ConsoleMessageType::Error,
            .text = text,
    });
}

void ZenEdit::Console::warn(const std::string &text) {
    messages.emplace_back(ConsoleMessage{
            .type = ConsoleMessageType::Warning,
            .text = text,
    });
}
void ZenEdit::Console::render() {
    for (const ConsoleMessage &message: Console::messages) {
        FontManager::set({
                                 .fontSize = 16.0f,
                                 .font = Font::Monospace,
                                 .textColor = typeToColor(message.type),
                         },
                         [&]() {
                             Label(message.text.c_str()).render();
                         });
    }
}
