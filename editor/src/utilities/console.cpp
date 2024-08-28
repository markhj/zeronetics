#include "console.h"

std::vector<ZenEdit::ConsoleMessage> ZenEdit::Console::messages;

void ZenEdit::Console::add(const std::string &text) {
    messages.emplace_back(ConsoleMessage{.text = text});
}
