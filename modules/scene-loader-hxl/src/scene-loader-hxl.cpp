#include "scene-loader-hxl/scene-loader-hxl.h"
#include "zeronetics/entities/3d/camera-3d.h"
#include "zeronetics/entities/3d/mesh-3d.h"
#include "zeronetics/scene/scene.h"
#include "zeronetics/shapes/3d/cube.h"

#include "hxl-lang/hxl-lang.h"
#include "zeronetics/logging/logging.h"

HXL::Schema schema;

HXL::DeserializationProtocol deserializationProtocol;

std::shared_ptr<ZEN::Camera3D> camera3d;

std::vector<std::shared_ptr<ZEN::IRenderable3D>> list_mesh3d;

namespace {
    void setVec3(ZEN::Vec3 *vec,
                 const char *key,
                 const std::map<std::string, HXL::DeserializedNodeProperty> &data) {
        auto it = data.find(key);
        if (it != data.end()) {
            if (!std::holds_alternative<std::vector<ZEN::gw_float>>((*it).second.value)) {
                ZEN_WARN("Vector values must be given in float values.", ZEN::LogCategory::DataFileIntegrity);
                *vec = ZEN::Vec3(0);
            } else {
                auto pos = std::get<std::vector<ZEN::gw_float>>((*it).second.value);
                *vec = ZEN::Vec3(pos[0], pos[1], pos[2]);
            }
        } else {
            *vec = ZEN::Vec3(0);
        }
    }
}

ZEN::SceneLoaderHxl::SceneLoaderHxl() {
    schema.types.push_back({"Mesh3D"});
    schema.types[0].properties.push_back({"position", HXL::DataType::Float, HXL::ValueStructure::Array});

    schema.types.push_back({"Camera3D"});
    schema.types[0].properties.push_back({"position", HXL::DataType::Float, HXL::ValueStructure::Array});
    schema.types[0].properties.push_back({"target", HXL::DataType::Float, HXL::ValueStructure::Array});

    HXL::DeserializationHandle mesh{"Mesh3D"};
    mesh.handle = [&](const HXL::DeserializedNode &node) {
        std::shared_ptr<Mesh3D> mesh = std::make_shared<Mesh3D>(std::make_shared<Cube>(Cube(0.5)));
        setVec3(&mesh->position, "position", node.properties);
        list_mesh3d.emplace_back(mesh);
    };

    HXL::DeserializationHandle ds_camera3d{"Camera3D"};
    ds_camera3d.handle = [&](const HXL::DeserializedNode &node) {
        camera3d = std::make_shared<Camera3D>(Camera3D());
        setVec3(&camera3d->position, "position", node.properties);
        setVec3(&camera3d->target, "target", node.properties);
    };

    deserializationProtocol.handles.push_back(mesh);
    deserializationProtocol.handles.push_back(ds_camera3d);
}

std::shared_ptr<ZEN::IScene> ZEN::SceneLoaderHxl::load(const ZEN::File &file) {
    auto source = file.getData();
    if (source.isError()) {
        throw std::runtime_error(std::format("Could not read HXL source."));
    }

    std::shared_ptr<Scene> scene = std::make_shared<Scene>(Scene());
    HXL::ProcessResult result = HXL::Processor::process(source.result(), schema, deserializationProtocol);

    for (const auto &mesh3d: list_mesh3d) {
        scene->add(mesh3d);
    }

    if (camera3d) {
        scene->camera3d = camera3d;
    }

    return scene;
}
