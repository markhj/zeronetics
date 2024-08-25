#include "project.h"
#include "hxl-lang/hxl-lang.h"
#include "hxl-serializer/hxl-serializer.h"
#include "scene.h"
#include <iostream>

namespace {
    HXL::Schema schema;

    HXL::DeserializationProtocol deserializationProtocol;

    std::string projectName;
    std::vector<ZenEdit::Scene> projectScenes;
}

ZenEdit::Project::Project() {
    schema.types.push_back({"Project"});
    schema.types[0].properties.push_back({.name = "name",
                                          .dataType = HXL::DataType::String,
                                          .required = true});

    schema.types.push_back({"Scene"});

    HXL::DeserializationHandle dsProject{"Project"};
    dsProject.handle = [&](const HXL::DeserializedNode &node) {
        auto it = node.properties.find("name");
        projectName = it != node.properties.end() ? std::get<std::string>((*it).second.value) : "";
    };

    HXL::DeserializationHandle dsScene{"Scene"};
    dsScene.handle = [&](const HXL::DeserializedNode &node) {
        projectScenes.emplace_back(Scene{
                .name = node.name,
        });
    };

    deserializationProtocol.handles.push_back(dsProject);
    deserializationProtocol.handles.push_back(dsScene);
}

void ZenEdit::Project::reset() {
    name.clear();
}

void ZenEdit::Project::load(const Path &path) {
    reset();

    m_path = path;

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

    name = projectName;
    scenes = projectScenes;
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
            },
    };

    nodes.emplace_back(nodeProject);

    unsigned int i = 1;
    for (const Scene &scene: scenes) {
        HxlNode sceneNode{
                .type = "Scene",
                .name = scene.name,
                .properties = {
                },
        };

        ++i;

        nodes.emplace_back(sceneNode);
    }

    hxlSource.setData(HxlSerializer::serialize({
            .nodes = nodes,
    }));
}
