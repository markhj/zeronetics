#include "project.h"
#include "../console.h"
#include "hxl-lang/hxl-lang.h"
#include "hxl-serializer/hxl-serializer.h"
#include "scene.h"
#include <iostream>

namespace {
    HXL::Schema schema;

    HXL::DeserializationProtocol deserializationProtocol;

    ZenEdit::Project *target;

    std::string useHxlDataDir = "hxl-data";
    Path *usePath = nullptr;
}

ZenEdit::Project::Project() {
    schema.types.push_back({"Project"});
    schema.types[0].properties.push_back({.name = "name",
                                          .dataType = HXL::DataType::String,
                                          .required = true});
    schema.types[0].properties.push_back({.name = "hxldir",
                                          .dataType = HXL::DataType::String,
                                          .required = true});

    schema.types.push_back({"Scene"});

    HXL::DeserializationHandle dsProject{"Project"};
    dsProject.handle = [&](const HXL::DeserializedNode &node) {
        auto it = node.properties.find("name");
        auto it2 = node.properties.find("hxldir");
        target->name = it != node.properties.end() ? std::get<std::string>((*it).second.value) : "";
        target->hxlDataDir = it != node.properties.end() ? std::get<std::string>((*it2).second.value) : "";
        useHxlDataDir = target->hxlDataDir;
    };

    HXL::DeserializationHandle dsScene{"Scene"};
    dsScene.handle = [&](const HXL::DeserializedNode &node) {
        auto it = node.properties.find("path");
        std::string path = useHxlDataDir + "/" + std::get<std::string>((*it).second.value);
        Scene scene;
        scene.name = node.name;
        scene.path = Path(usePath->getAbsolute() + "/" + path);
        target->scenes.emplace_back(scene);
    };

    deserializationProtocol.handles.push_back(dsProject);
    deserializationProtocol.handles.push_back(dsScene);
}

void ZenEdit::Project::reset() {
    activeScene.reset();
    name.clear();
}

void ZenEdit::Project::load(const Path &path) {
    reset();

    target = this;

    m_path = path;
    usePath = &m_path.value();

    Path hxlProject(path.getAbsolute() + "/project.hxl");

    File hxlSource(hxlProject);
    auto loadSource = hxlSource.getData();

    if (loadSource.isError()) {
        throw std::runtime_error(loadSource.error().errorMessage.value());
    }

    std::string source = loadSource.result();
    HXL::ProcessResult result = HXL::Processor::process(source, schema, deserializationProtocol);

    if (!result.errors.empty()) {
        throw std::runtime_error(result.errors[0].message);
    }
}

void ZenEdit::Project::save() {
    Path hxlProject(m_path->getAbsolute() + "/project.hxl");
    File hxlSource(hxlProject);
    std::vector<HxlNode> nodes;

    HxlNode nodeProject{
            .type = "Project",
            .name = "Project",
            .properties = {
                    {"name", HxlNodeValue{HxlDataType::String, {name}}},
                    {"hxldir", HxlNodeValue{HxlDataType::String, {hxlDataDir}}},
            },
    };

    nodes.emplace_back(nodeProject);

    unsigned int i = 1;
    for (Scene &scene: scenes) {
        scene.createFileIfNotExists();
        HxlNode sceneNode{
                .type = "Scene",
                .name = scene.name,
                .properties = {
                        {"path", HxlNodeValue{HxlDataType::String, {scene.name + ".hxl"}}},
                },
        };

        ++i;

        nodes.emplace_back(sceneNode);
    }

    hxlSource.setData(HxlSerializer::serialize({
            .nodes = nodes,
    }));

    Console::info("Project saved.");
}

Path ZenEdit::Project::getPath(const char *subPath) {
    return Path(m_path->getAbsolute() + "/" + subPath);
}
