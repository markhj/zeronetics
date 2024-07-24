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

    auto elapsed = std::chrono::high_resolution_clock::now() - m_startTime.value();
    auto microsecs = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();

    return Result<TimeMeasurement>{TimeMeasurement{microsecs}};
}

void ZEN::Timer::reset() {
    m_startTime = std::chrono::high_resolution_clock::now();
}

void ZEN::Timer::end() {
    m_startTime = std::nullopt;
}

float ZEN::TimeMeasurement::toSeconds() const noexcept {
    return static_cast<float>(microsecs) / 1000000.0f;
}
