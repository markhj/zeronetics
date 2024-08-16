#include "scene-loader-hxl/scene-loader-hxl.h"
#include "zeronetics/entities/3d/camera-3d.h"
#include "zeronetics/entities/3d/mesh-3d.h"
#include "zeronetics/scene/scene.h"
#include "zeronetics/shapes/3d/cube.h"

#include "hxl-lang/hxl-lang.h"
#include "zeronetics/contracts/shader-builder.h"
#include "zeronetics/logging/logging.h"

namespace {
    HXL::Schema schema;

    HXL::DeserializationProtocol deserializationProtocol;

    std::shared_ptr<ZEN::Camera3D> camera3d;

    std::vector<std::shared_ptr<ZEN::IRenderable3D>> listMesh3d;

    std::unordered_map<std::string, std::shared_ptr<ZEN::Cube>> listCubes;

    std::unordered_map<std::string, std::shared_ptr<ZEN::ShaderBlueprint>> listShaderBlueprints;

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
    schema.types[0].properties.push_back({"shape", HXL::DataType::NodeRef});

    schema.types.push_back({"Cube"});
    schema.types[0].properties.push_back({"size", HXL::DataType::Float, HXL::ValueStructure::Array});

    schema.types.push_back({"ShaderBuilder"});
    schema.types[0].properties.push_back({"color", HXL::DataType::Float, HXL::ValueStructure::Array});

    schema.types.push_back({"Camera3D"});
    schema.types[0].properties.push_back({"position", HXL::DataType::Float, HXL::ValueStructure::Array});
    schema.types[0].properties.push_back({"target", HXL::DataType::Float, HXL::ValueStructure::Array});

    HXL::DeserializationHandle dsCube{"Cube"};
    dsCube.handle = [&](const HXL::DeserializedNode &node) {
        auto it = node.properties.find("size");
        auto size = std::get<std::vector<ZEN::gw_float>>((*it).second.value);
        std::shared_ptr<Cube> cube = std::make_shared<Cube>(Cube(size[0], size[1], size[2]));
        listCubes[node.name] = cube;
    };

    HXL::DeserializationHandle dsMesh{"Mesh3D"};
    dsMesh.handle = [&](const HXL::DeserializedNode &node) {
        Cube makeCube(0.5);
        auto it = node.properties.find("shape");
        if (it != node.properties.end()) {
            std::string ref = std::get<HXL::NodeRef>((*it).second.value).references;
            auto it2 = listCubes.find(ref);
            if (it2 != listCubes.end()) {
                makeCube = *it2->second;
            }
        }

        std::shared_ptr<Mesh3D> mesh = std::make_shared<Mesh3D>(std::make_shared<Cube>(makeCube));
        setVec3(&mesh->position, "position", node.properties);
        listMesh3d.emplace_back(mesh);
    };

    HXL::DeserializationHandle dsCamera3d{"Camera3D"};
    dsCamera3d.handle = [&](const HXL::DeserializedNode &node) {
        camera3d = std::make_shared<Camera3D>(Camera3D());
        setVec3(&camera3d->position, "position", node.properties);
        setVec3(&camera3d->target, "target", node.properties);
    };

    HXL::DeserializationHandle dsShaderBuilder{"ShaderBuilder"};
    dsShaderBuilder.handle = [&](const HXL::DeserializedNode &node) {
        std::shared_ptr<ShaderBlueprint> shaderBuilder = std::make_shared<ShaderBlueprint>(ShaderBlueprint());
        listShaderBlueprints[node.name] = shaderBuilder;
    };

    deserializationProtocol.handles.push_back(dsMesh);
    deserializationProtocol.handles.push_back(dsCamera3d);
    deserializationProtocol.handles.push_back(dsCube);
    deserializationProtocol.handles.push_back(dsShaderBuilder);
}

std::shared_ptr<ZEN::IScene> ZEN::SceneLoaderHxl::load(const ZEN::File &file) {
    auto source = file.getData();
    if (source.isError()) {
        throw std::runtime_error(std::format("Could not read HXL source."));
    }

    std::shared_ptr<Scene> scene = std::make_shared<Scene>(Scene());
    HXL::ProcessResult result = HXL::Processor::process(source.result(), schema, deserializationProtocol);

    for (const auto &mesh3d: listMesh3d) {
        scene->add(mesh3d);
    }

    if (camera3d) {
        scene->camera3d = camera3d;
    }

    return scene;
}
