#pragma once

#include <memory>

#include "shader.h"
#include "transforms.h"
#include "zeronetics/core/tensors.h"

namespace ZEN {
    class ICamera {
    public:
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

        virtual void setOnShader(const std::string &key,
                                 const std::shared_ptr<IShader> &shader) = 0;

    };
}
