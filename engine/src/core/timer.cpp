#include "zeronetics/core/timer.h"

void ZEN::Timer::start() {
    m_startTime = std::chrono::high_resolution_clock::now();
}

ZEN::Result<ZEN::TimeMeasurement> ZEN::Timer::getTime() {
    if (!m_startTime.has_value()) {
        return ResultError{
                .errorMessage = "Timer not started.",
        };
    }

    return ZEN::TimeMeasurement{
            std::chrono::duration_cast<std::chrono::microseconds>(
                    std::chrono::high_resolution_clock::now() - m_startTime.value())
                    .count()
    };
}

void ZEN::Timer::reset() {
    m_startTime = std::chrono::high_resolution_clock::now();
}

void ZEN::Timer::end() {
    m_startTime = std::nullopt;
}

float ZEN::TimeMeasurement::toSeconds() const noexcept {
    return microsecs / 1000000;
}
