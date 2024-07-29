#include "control-systems/free-camera.h"

#include "zeronetics/core/globals.h"
#include "zeronetics/logging/log.h"
#include "zeronetics/logging/logging.h"

namespace {
    bool hasSignal(const std::string &signal,
                   const std::vector<std::string> &signals) {
        auto it = std::find(signals.begin(), signals.end(), signal);
        return it != signals.end();
    }
}

void ZEN::ControlSystems::FreeCamera::process(dt_float delta,
                                              const std::vector<std::string> &incomingSignals) {
    if (!signals[0] || !signals[1] || !signals[2] || !signals[3]) {
        ZEN_WARN("You must declare all four signals in Free Camera.", ZEN::LogCategory::Controls);
        return;
    }

    if (!camera3d) {
        ZEN_WARN("You must define a camera in Free Camera.", ZEN::LogCategory::Controls);
        return;
    }

    bool forward = hasSignal(signals[0], incomingSignals);
    bool left = hasSignal(signals[1], incomingSignals);
    bool backward = hasSignal(signals[2], incomingSignals);
    bool right = hasSignal(signals[3], incomingSignals);

    Vec2 direction(0.0, 0.0);
    if (forward) {
        direction.y = 1.0;
    } else if (backward) {
        direction.y = -1.0;
    }

    if (left) {
        direction.x = 1.0;
    } else if (right) {
        direction.x = -1.0;
    }

    if (direction.y != 0.0 || direction.x != 0.0) {
        gw_float angle = xzAngle - atan2(direction.y, direction.x) + M_PI / 2.0;
        gw_float changeY = direction.y != 0.0 ? sin(M_PI * 0.5 * yAngle) : 0.0;
        if (direction.y == -1.0) {
            changeY *= -1.0;
        }

        Vec3 diff = delta * Vec3(sin(angle), changeY, cos(angle));

        camera3d->position += diff;
        camera3d->target += diff;
    }
}

void ZEN::ControlSystems::FreeCamera::onMouseMoved(const ZEN::MouseMovedEvent &mouseMovedEvent) {
    xzAngle -= mouseMovedEvent.relative.x * 0.01;

    auto screenY = Globals::viewportSize.h;
    auto half = screenY / 2.0;

    yAngle = (half - mouseMovedEvent.position.y) / half;

    camera3d->target = camera3d->position + Vec3(sin(xzAngle), sin(M_PI * 0.5 * yAngle), cos(xzAngle));
}

bool ZEN::ControlSystems::FreeCamera::isInitialized() const noexcept {
    return initialized;
}

ZEN::ControlSystems::AssistInitialization ZEN::ControlSystems::FreeCamera::initialize() {
    xzAngle = atan2(camera3d->target.z - camera3d->position.z, camera3d->target.x - camera3d->position.x);
    yAngle = atan2(camera3d->target.y, camera3d->position.y);

    std::vector<const char *> res;
    std::for_each(signals.begin(), signals.end(), [&](const auto &item) {
        res.emplace_back(item);
    });

    initialized = true;

    return {
            .signals = res,
    };
}
