#pragma once

#include <memory>

#include "shader.h"
#include "zeronetics/core/attributes.h"

namespace ZEN {
    class ILight {
    public:
        ColorRGB color = ColorRGB(1.0, 1.0, 1.0);

        virtual void setOnShader(const std::string &key,
                                 const std::shared_ptr<ZEN::IShader> &shader) = 0;
    };

    class IPointLight : public ILight {
    public:
        float constant = 1.0,
              linear = 0.01,
              quadratic = 0.032;
    };
}
