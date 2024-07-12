#pragma once

#include "zeronetics/contracts/renderer.h"

namespace ZEN {
    class OpenGLRenderer : public IRenderer {
    public:
        void render() override;

    };
}
