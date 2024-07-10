#pragma once

namespace ENGINE_NAMESPACE {
    /**
     * Game world floating-point type
     *
     * Should be used for any application of floating-point numbers
     * in the game world, such as vector coordinates.
     *
     * In most cases ``float`` suffices, but large game worlds
     * may benefit from, or require, a floating-point type with higher precision.
     */
    typedef float gw_float;

    /**
     * Delta floating-point type
     *
     * The floating-point type applied to measure
     * delta time intervals.
     */
    typedef float dt_float;
}
