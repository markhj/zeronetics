#pragma once

#include <chrono>

#include "result.h"
#include "typedefs.h"

namespace ZEN {
    /**
     * Struct containing a time measurement.
     * The value is by default given in microseconds.
     */
    struct TimeMeasurement {
        /**
         * Micro-seconds
         */
        long long microsecs = 0;

        /**
         * Convert micro-seconds to seconds.
         *
         * @return
         */
        float toSeconds() const noexcept;
    };

    /**
     * Timer
     *
     * Measure time intervals with ease.
     *
     * @ref timer
     */
    class Timer {
    public:
        /**
         * Start the timer.
         */
        void start();

        /**
         * Reset the timer, but keep it running.
         */
        void reset();

        /**
         * Finish time measurement.
         */
        void end();

        /**
         * Get current time measurement.
         * This method can be called multiple times.
         *
         * @note You will get an error, if the timer isn't started.
         *
         * @return
         */
        Result<TimeMeasurement> getTime();

    private:
        /**
         * Contains the time the timer started.
         */
        std::optional<std::chrono::time_point<std::chrono::high_resolution_clock>> m_startTime;


    };
}
