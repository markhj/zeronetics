#include "extension-list.h"

#include "box.h"
#include "button.h"
#include "zeronetics/entities/entity.h"

ZenEdit::ExtensionList::ExtensionList(bool *showBox) : m_showBox(showBox) {
}

void ZenEdit::ExtensionList::render() {
    Box box("Add Entity");
    box.contains([&]() {
        for (const auto &item: ZEN::EntityRegistry::getEntities()) {
            Button button;
            button.text = item.first;
            button.onClick = [&]() {
                onCreateEntity(*item.second);
            };
            button.render();
        }
    });
    box.render();
}
