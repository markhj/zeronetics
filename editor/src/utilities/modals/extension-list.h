#pragma once

#include "../editor-utility.h"
#include "zeronetics/entities/entity.h"
#include <functional>
#include <string>

using namespace ZEN;

namespace ZenEdit {
    class ExtensionList : public EditorUtility {
    public:
        explicit ExtensionList(bool *showBox);

        void render() override;

        std::function<void(const EntityRegistration &entityName)> onCreateEntity = [&](const EntityRegistration &entityName) {};

    private:
        bool *m_showBox;

    };
}
