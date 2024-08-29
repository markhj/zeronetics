#include "about.h"
#include "../font-manager.h"
#include "box.h"
#include "button.h"
#include "label.h"
#include "separator.h"

ZenEdit::About::About(bool *showBox) : m_showBox(showBox) {
}

void ZenEdit::About::render() {
    Box box("About ZenEdit");
    box.collapsible = false;
    box.resizable = false;
    box.contains([&]() {
        FontManager::set({.fontSize = 24.0}, [&]() {
            Label("ZenEdit").render();
        });

        Separator().render();
        Label("This is the editor for the Zeronetics game engine.").render();

        Button okButton;
        okButton.text = "OK";
        okButton.onClick = [&]() { *m_showBox = false; };
        okButton.render();
    });
    box.render();
}
