#include "editor.h"

#include "autoload.cpp"

int main() {
    Autoload::registerEntities();

    ZenEdit::Editor editor;
    editor.initialize();
    editor.run();
}
