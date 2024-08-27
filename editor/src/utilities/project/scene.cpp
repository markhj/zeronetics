#include "scene.h"
#include "hxl-serializer/hxl-serializer.h"
#include <iostream>
#include <vector>

void ZenEdit::Scene::save() {
    File hxlSource(path.value());
    std::vector<HxlNode> nodes;

    for (const auto &entity: entities) {
        HxlNode sceneNode{
                .type = "Entity",
                .name = entity.first,
                .properties = {},
        };

        nodes.emplace_back(sceneNode);
    }

    hxlSource.setData(HxlSerializer::serialize({
            .nodes = nodes,
    }));
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
