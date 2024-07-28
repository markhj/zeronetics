#pragma once

#include "zeronetics/contracts/lights.h"
#include "zeronetics/contracts/transforms.h"

namespace ZEN {
    class PointLight3D : public IPointLight,
                          public IPosition3D {
    public:
        void setOnShader(const std::string &key,
                         const std::shared_ptr<ZEN::IShader> &shader) override;
    };
}
