#include "scene.h"
#include <iostream>

void ZenEdit::Scene::save() {

}

void ZenEdit::Scene::load() {
    createFileIfNotExists();

    File file(path.value());
    auto fileData = file.getData();
    if (fileData.isError()) {
        throw std::runtime_error("Failed to load scene file: " + path->getAbsolute());
    }

    std::string fileSource = fileData.result();
}

void ZenEdit::Scene::createFileIfNotExists() {
    if (!path.has_value()) {
        throw std::runtime_error("Expected file to exist at this point.");
    }

    if (path->exists()) {
        return;
    }

    File file(path.value());
    file.createIfNotExists();
    file.setData("\n");
}
