#include "scene.h"
#include "hxl-lang/core.h"
#include "hxl-lang/services/processor.h"
#include "hxl-serializer/hxl-serializer.h"
#include <iostream>
#include <vector>

namespace {
    HXL::Schema schema;

    HXL::DeserializationProtocol deserializationProtocol;

    std::map<std::string, ZenEdit::SceneEntity> makeEntities;
}

ZenEdit::Scene::Scene() {
    schema.types.push_back({"Entity"});

    HXL::DeserializationHandle dsEntity{"Entity"};
    dsEntity.handle = [&](const HXL::DeserializedNode &node) {
        makeEntities[node.name];
    };

    deserializationProtocol.handles.push_back(dsEntity);
}

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

    std::string source = fileData.result();
    HXL::ProcessResult result = HXL::Processor::process(source, schema, deserializationProtocol);

    if (!result.errors.empty()) {
        throw std::runtime_error(result.errors[0].message);
    }

    entities = makeEntities;

    makeEntities.clear();
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
