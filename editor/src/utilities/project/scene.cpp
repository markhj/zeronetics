#include "scene.h"

void ZenEdit::Scene::save() {

}

void ZenEdit::Scene::load() {
    createFileIfNotExists();


}

void ZenEdit::Scene::createFileIfNotExists() {
    if (!path.has_value()) {
        throw std::runtime_error("Expected file to exist at this point.");
    }

    if (path->exists()) {
        return;
    }

    File(path.value()).setData("\n");
}
