#include "hxl-serializer/hxl-serializer.h"
#include <cassert>
#include <format>


std::string ZEN::HxlSerializer::serialize(const ZEN::HxlDocument &document) {
    std::string source;

    for (const HxlNode &node: document.nodes) {
        source += std::format("<{}> {}\n", node.type, node.name);
        for (const auto &property: node.properties) {
            switch (property.second.dataType) {
                case HxlDataType::String:
                    source += std::format("\t{}: \"{}\"\n", property.first, property.second.values[0]);
                    break;
                default:
                    assert(false && "Data type not specified in HxlSerializer::serialize.");
            }
        }
        source += "\n";
    }

    return source;
}
