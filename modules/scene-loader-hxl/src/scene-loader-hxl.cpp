#include "scene-loader-hxl/scene-loader-hxl.h"
#include "zeronetics/entities/3d/mesh-3d.h"
#include "zeronetics/scene/scene.h"
#include "zeronetics/shapes/3d/cube.h"

#include "hxl-lang/hxl-lang.h"
#include "zeronetics/logging/logging.h"

HXL::Schema schema;

HXL::DeserializationProtocol deserializationProtocol;

std::vector<std::shared_ptr<ZEN::IRenderable3D>> list_mesh3d;

ZEN::SceneLoaderHxl::SceneLoaderHxl() {
    schema.types.push_back({"Mesh3D"});
    schema.types[0].properties.push_back({"position", HXL::DataType::Float, HXL::ValueStructure::Array});

    HXL::DeserializationHandle mesh {"Mesh3D"};
    mesh.handle = [&](const HXL::DeserializedNode &node) {
        auto mesh = std::make_shared<Mesh3D>(std::make_shared<Cube>(Cube(0.5)));
        auto it = node.properties.find("position");
        if (it != node.properties.end()) {
            if (!std::holds_alternative<std::vector<gw_float>>((*it).second.value)) {
                ZEN_WARN("Mesh positions must be given in float values.", ZEN::LogCategory::DataFileIntegrity);
                mesh->position = Vec3(0);
            } else {
                auto pos = std::get<std::vector<gw_float>>((*it).second.value);
                mesh->position = Vec3(pos[0], pos[1], pos[2]);
            }
        } else {
            mesh->position = Vec3(0);
        }
        list_mesh3d.emplace_back(mesh);
    };
    deserializationProtocol.handles.push_back(mesh);
}

std::shared_ptr<ZEN::IScene> ZEN::SceneLoaderHxl::load(const ZEN::File &file) {
    auto source = file.getData();
    if (source.isError()) {
        throw std::runtime_error(std::format("Could not read HXL source."));
    }

    std::shared_ptr<Scene> scene = std::make_shared<Scene>(Scene());
    HXL::ProcessResult result = HXL::Processor::process(source.result(), schema, deserializationProtocol);

    for (const auto mesh3d: list_mesh3d) {
        scene->add(mesh3d);
    }

    return scene;
}
