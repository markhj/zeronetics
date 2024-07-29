#pragma once

#include <memory>

#include "shader.h"
#include "transforms.h"
#include "zeronetics/core/tensors.h"

namespace ZEN {
    /**
     * Camera Contract
     */
    class ICamera {
    public:
        /**
         * All cameras must implement a function which can specify
         * uniform data about the camera on a shader.
         *
         * @param key
         * @param shader
         */
        virtual void setOnShader(const std::string &key,
                                 const std::shared_ptr<IShader> &shader) = 0;

    };

    /**
     * 3D camera contract
     *
     * @ref camera-3d
     */
    class ICamera3D : public ITransforms3D {
    public:
        /**
         * Target (i.e. what the camera is looking at)
         */
        Vec3 target = Vec3(0.0);

        /**
         * Which direction is upward.
         */
        Vec3 up = Vec3(0.0, 1.0, 0.0);

        /**
         * Calculate the Model-View-Projection (MVP) matrix.
         *
         * @return
         */
        [[nodiscard]] virtual MVP getModelViewProjection() const noexcept = 0;

        /**
         * Set information about the camera on the shader.
         *
         * @param key
         * @param shader
         */
        virtual void setOnShader(const std::string &key,
                                 const std::shared_ptr<IShader> &shader) = 0;

    };
}
