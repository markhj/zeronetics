#pragma once

#include "opengl-renderer/opengl.h"

#include "opengl-object.h"
#include "vbo.h"
#include "zeronetics/core/enums.h"

#include <vector>

namespace ZEN::OpenGL {
    class VAO : public Object {
    public:
        void initialize() noexcept(false);

        void attachVBO(const std::shared_ptr<VBO> &vbo,
                       const std::vector<VertexAttribute> &attributes) noexcept(false);

        void bindTo(gl_uint context) override;

        [[nodiscard]] gl_uint getContextId() const override;

    protected:
        [[nodiscard]] std::optional<gl_uint> getCurrentContextId() const override;

    private:
        gl_uint id = 0;

        std::vector<std::shared_ptr<VBO>> m_vbos;

    };
}
