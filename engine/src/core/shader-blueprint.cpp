#include "zeronetics/core/shader-blueprint.h"

bool ZEN::LightSupport::hasAnyLight() const noexcept {
    if (slotsDirectionalLight3D > 0) {
        return true;
    }

    if (slotsPointLight3D > 0) {
        return true;
    }

    return false;
}
