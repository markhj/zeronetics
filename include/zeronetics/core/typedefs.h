#pragma once

#include <cstdint>
namespace ZEN {
    /**
     * Game world floating-point type
     *
     * Should be used for any application of floating-point numbers
     * in the game world, such as vector coordinates.
     *
     * In most cases ``float`` suffices, but large game worlds
     * may benefit from, or require, a floating-point type with higher precision.
     *
     * @ref gw-float
     */
    typedef float gw_float;

    /**
     * Delta floating-point type
     *
     * The floating-point type applied to measure
     * delta time intervals.
     *
     * @ref delta
     */
    typedef float dt_float;

    /**
     * Mouse position
     *
     * The data type mouse/cursor position is stored
     * and reported with.
     *
     * Most of the time, this does not cause any issues,
     * but should probably be set to match the window implementation.
     */
    typedef double mouse_pos_axis;

    /**
     * Unique ID
     *
     * An integer-based type which can hold sufficient numbers
     * to attribute every object which requires a unique ID.
     */
    typedef uint32_t unique_id;

    /**
     * Data type used to map index and size
     * of renderables allocated in the GPU.
     */
    typedef unsigned int gpu_alloc_int;

    /**
     * The type for storing and reading elapsed time between
     * frames in the game loop.
     *
     * @ref fps
     */
    typedef long long render_time_microsecs;

    /**
     * Value for frames per second (FPS)
     *
     * @ref fps
     */
    typedef uint16_t fps_int;
}
