#pragma once

#include "zeronetics/contracts/cameras.h"
#include "zeronetics/core/tensors.h"
#include "zeronetics/core/typedefs.h"
#include "zeronetics/entities/entity.h"

#include <memory>

namespace ZEN {
    /**
     * Implementation of 3D camera.
     *
     * @ref camera-3d
     */
    class Camera3D : public Entity3D,
                     public ICamera3D {
    public:
        EntityRegistration getRegistration() override;

        /**
         * Aspect ratio
         * Default: Approx. 1920 x 1080
         */
        gw_float aspectRatio = 1.777;

        /**
         * Field of view (in Y-direction):
         * Default: 45 degrees in radians
         */
        gw_float fieldOfView = 0.785398;

        /**
         * The clipping plane, where first value is nearest
         * and second is furthest.
         */
        std::array<gw_float , 2> clippingPlane = {0.1, 100.0};

        /**
         * Calculate the individual components for the Model-View-Perspective
         * (MVP) matrix using the current camera position, target, up and configuration.
         *
         * @return
         */
        [[nodiscard]] MVP getModelViewProjection() const noexcept override;

        /**
         * Instruct the shader on properties of this camera.
         *
         * @param key
         * @param shader
         */
        void setOnShader(const std::string &key,
                         const std::shared_ptr<IShader> &shader) override;
    };
}
