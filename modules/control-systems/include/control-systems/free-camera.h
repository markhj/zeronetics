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

        /**
         * The minimum distance of the target.
         */
        gw_float minDistance = 0.5;

        /**
         * The maximum distance to the target.
         */
        gw_float maxDistance = 3.0;

        /**
         * The distance decreased/increased per request.
         */
        gw_float distanceSteps = 0.5;

        void process(dt_float delta,
                     const std::vector<std::string> &signals) override;

        void onMouseMoved(const MouseMovedEvent &mouseMovedEvent) override;

        void onScroll(const ScrollEvent &scrollEvent) override;

        void initialize() override;

        std::vector<const char *> getSignals() override;

    private:
        gw_float m_distance = 1.0;

        gw_float xzAngle = 0.0,
                 yAngle = 0.0;
    };
}
