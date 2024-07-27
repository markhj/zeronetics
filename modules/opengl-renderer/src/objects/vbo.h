#pragma once

#include "opengl-object.h"
#include "opengl-renderer/opengl.h"

namespace ZEN::OpenGL {
    /**
     * Vertex Buffer Object
     *
     * @ref opengl-allocation
     */
    class VBO : public OpenGL::Object {
    public:
        /**
         * Initialize the context
         */
        void initialize() noexcept(false);

        /**
         * Make this VBO active.
         *
         * @param context
         */
        void bindTo(gl_uint context) override;

        /**
         * Get this VBO's ID.
         *
         * @return
         */
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

        /**
         * Deallocate a segment of the GPU buffer.
         */
        void deallocate(gpu_alloc_int from, gpu_alloc_int size);

        /**
         * Update data at the specified location (allocation).
         *
         * @param allocation
         * @param data
         */
        void updateData(const GPUAllocation &allocation,
                        const std::vector<gl_float> &data);

        /**
         * Get the size currently allocated for the VBO.
         *
         * @return
         */
        [[nodiscard]] gpu_alloc_int getCurrentSize() const noexcept;

    protected:
        [[nodiscard]] std::optional<gl_uint> getCurrentContextId() const override;

    private:
        gl_uint id = 0;

        gpu_alloc_int currentAllocIndex = 0,
                      currentSize = 0;

    };
}
