#include "ui-element.h"

void ZenEdit::UIContainer::render() {
    start();
    if (m_contains.has_value()) {
        m_contains.value()();
    }
    end();
}

void ZenEdit::UIContainer::contains(const std::function<void()> &func) {
    m_contains = func;
}
