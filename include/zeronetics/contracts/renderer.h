#pragma once

namespace ZEN {
    /**
     * Renderer contract
     */
    class IRenderer {
    public:
        virtual void initialize() = 0;

        virtual bool isInitialized() const noexcept = 0;

        virtual void clear() noexcept = 0;

        virtual void render() = 0;

    };
}
