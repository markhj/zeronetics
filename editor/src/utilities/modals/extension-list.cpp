#include "extension-list.h"
#include "label.h"

#include "zeronetics/entities/entity.h"

ZenEdit::ExtensionList::ExtensionList(bool *showBox) : m_showBox(showBox) {
}

void ZenEdit::ExtensionList::render() {
    for (const auto &item: ZEN::EntityRegistry::getEntities()) {
        Label(item.first).render();
    }
}
