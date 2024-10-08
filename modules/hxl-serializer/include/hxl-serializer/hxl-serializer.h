#pragma once

#include <string>
#include <map>
#include <vector>

namespace ZEN {
    enum class HxlDataType {
        String,
    };

    struct HxlNodeValue {
        HxlDataType dataType;
        std::vector<std::string> values;
    };

    struct HxlNode {
        std::string type, name;
        std::map<std::string, HxlNodeValue> properties;
    };

    struct HxlDocument {
        std::vector<HxlNode> nodes;
    };

    class HxlSerializer {
    public:
        static std::string serialize(const HxlDocument &document);

    };
}
