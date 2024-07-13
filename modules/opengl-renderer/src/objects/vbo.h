#pragma once

#include "opengl-object.h"
#include "opengl-renderer/opengl.hpp"

namespace ZEN {
    class VBO : public OpenGL::Object {
    public:
        void initialize() noexcept(false);

        void bindTo(gl_uint context) override;

        [[nodiscard]] gl_uint getContextId() const override;

    protected:
        [[nodiscard]] std::optional<gl_uint> getCurrentContextId() const override;

    private:
        gl_uint id = 0;

    };
}
