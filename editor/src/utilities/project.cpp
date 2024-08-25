#include "project.h"
#include "hxl-lang/hxl-lang.h"
#include <iostream>


namespace {
    HXL::Schema schema;

    HXL::DeserializationProtocol deserializationProtocol;

    std::string projectName;
}

ZenEdit::Project::Project() {
    schema.types.push_back({"Project"});
    schema.types[0].properties.push_back({.name = "name",
                                          .dataType = HXL::DataType::String,
                                          .required = true});

    HXL::DeserializationHandle dsProject{"Project"};
    dsProject.handle = [&](const HXL::DeserializedNode &node) {
        auto it = node.properties.find("name");
        projectName = it != node.properties.end() ? std::get<std::string>((*it).second.value) : "";
    };
    deserializationProtocol.handles.push_back(dsProject);
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
}

void ZenEdit::Project::save() {
    Path hxlProject(m_path->getAbsolute() + "/project.hxl");
    File hxlSource(hxlProject);

    hxlSource.setData(std::format("<Project>\n\tname: \"{}\"\n", name));
}
