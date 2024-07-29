#pragma once

#include "control-assist.h"
#include "zeronetics/core/typedefs.h"
#include "zeronetics/entities/3d/camera-3d.h"

#include <string>
#include <vector>

namespace ZEN::ControlSystems {
    class FreeCamera : public Assist {
    public:
        /**
         * Order: Forward, Left, Backward, Right
         */
        std::array<const char *, 4> signals;

        /**
         * The camera instance to be manipulated.
         */
        std::shared_ptr<ICamera3D> camera3d;

        void process(dt_float delta,
                     const std::vector<std::string> &signals) override;

        void onMouseMoved(const MouseMovedEvent &mouseMovedEvent) override;

        void initialize() override;

        std::vector<const char *> getSignals() override;

    private:
        gw_float xzAngle = 0.0,
                 yAngle = 0.0;
    };
}
