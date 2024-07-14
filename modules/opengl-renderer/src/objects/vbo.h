#pragma once

#include "opengl-object.h"
#include "opengl-renderer/opengl.hpp"

namespace ZEN {
    class VBO : public OpenGL::Object {
    public:
        void initialize() noexcept(false);

        void bindTo(gl_uint context) override;

        [[nodiscard]] gl_uint getContextId() const override;

        /**
         * Resize the VBO buffer
         *
         * @important Data on the buffer will be cleared, and you will
         *      have to re-allocate the vertices.
         *
         * @param size
         */
        void resize(gpu_alloc_int size);

        /**
         * Get an allocation block for X floats.
         *
         * @note You allocate spots for floats, not vertices.
         *      This means that if you want to allocate room for 3
         *      vertices with 2 properties with a size 6, you must
         *      request a block of 18 (3x6).
         *
         * @note When a ``std::nullopt`` was returned, it means
         *      there wasn't space in the VBO, and you will have
         *      to resize it.
         *
         * @note The reason this method doesn't automatically resize
         *      the buffer when needed, is that it will clear the buffer
         *      data, and this has to be managed elsewhere.
         *
         * @param size
         * @return
         */
        std::optional<GPUAllocation> allocate(gpu_alloc_int size);

        void setData(std::vector<gl_float> data);

        void updateData(const GPUAllocation &allocation,
                        const std::vector<gl_float> &data);

        [[nodiscard]] gpu_alloc_int getCurrentSize() const noexcept;

    protected:
        [[nodiscard]] std::optional<gl_uint> getCurrentContextId() const override;

    private:
        gl_uint id = 0;

        gpu_alloc_int currentAllocIndex = 0,
                      currentSize = 0;

    };
}
