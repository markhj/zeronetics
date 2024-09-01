#include "extension-list.h"

#include "button.h"
#include "zeronetics/entities/entity.h"

ZenEdit::ExtensionList::ExtensionList(bool *showBox) : m_showBox(showBox) {
}

void ZenEdit::ExtensionList::render() {
    for (const auto &item: ZEN::EntityRegistry::getEntities()) {
        Button button;
        button.text = item.first;
        button.onClick = [&]() {
            onCreateEntity(item.first);
        };
        button.render();
    }
}
