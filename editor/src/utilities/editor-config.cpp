#include "editor-config.h"
#include "hxl-lang/hxl-lang.h"
#include "hxl-serializer/hxl-serializer.h"
#include <format>


namespace {
    HXL::Schema schema;

    HXL::DeserializationProtocol deserializationProtocol;
}

ZenEdit::EditorConfig::EditorConfig() {
    schema.types.push_back({"Project"});
    schema.types[0].properties.push_back({.name = "path",
                                          .dataType = HXL::DataType::String,
                                          .required = true});

    HXL::DeserializationHandle dsProject{"Project"};
    dsProject.handle = [&](const HXL::DeserializedNode &node) {
        std::string path = std::get<std::string>((*node.properties.find("path")).second.value);
        Path pathInstance(path);

        // Only add the project if it exists and is a directory.
        // This means that if a project has been deleted, it is automatically
        // removed from the list.
        if (pathInstance.exists() && pathInstance.isDirectory()) {
            projects.emplace_back(path);
        }
    };

    deserializationProtocol.handles.push_back(dsProject);
}

void ZenEdit::EditorConfig::load() {
    if (!m_path.exists()) {
        return;
    }

    projects.clear();
    projects.reserve(10);

    auto loadSource = m_file.getData();
    if (loadSource.isError()) {
        throw std::runtime_error(loadSource.error().errorMessage.value());
    }

    std::string source = loadSource.result();
    HXL::ProcessResult result = HXL::Processor::process(source, schema, deserializationProtocol);

    if (!result.errors.empty()) {
        throw std::runtime_error(result.errors[0].message);
    }
}

void ZenEdit::EditorConfig::save() {
    HxlDocument document;

    unsigned int i = 1;
    for (const std::string &projectPath: projects) {
        document.nodes.emplace_back(HxlNode{
                .type = "Project",
                .name = std::format("Project{}", i),
                .properties = {
                        {"path", HxlNodeValue{.dataType = HxlDataType::String, .values = {projectPath}}},
                },
        });
        ++i;
    }

    m_file.createIfNotExists();
    m_file.setData(HxlSerializer::serialize(document));
}
