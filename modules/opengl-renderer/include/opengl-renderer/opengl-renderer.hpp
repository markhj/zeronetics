#pragma once

#include "zeronetics/contracts/renderer.h"

namespace ZEN {
    class OpenGLRenderer : public IRenderer {
    public:
        void initialize() override;

        [[nodiscard]] bool isInitialized() const noexcept override;

        void render() override;

        void clear() noexcept override;

    private:
        bool m_initialized = false;
    };
}
