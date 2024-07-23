#include "zeronetics/game/game.h"
#include <chrono>
#include <cmath>
#include <iostream>

ZEN::Game::Game(const std::shared_ptr<IWindow> &window,
                const std::shared_ptr<IRenderer> &renderer) : m_window(window),
                                                              m_renderer(renderer) {
}

void ZEN::Game::run() {
    if (!m_renderer->isInitialized()) {
        m_renderer->initialize();
    }

    m_timer.start();

    Timer fpsTimer;
    fpsTimer.start();

    while (keepOpen) {
        m_timer.reset();

        m_renderer->clear();

        processAll(m_delta);

        m_renderer->render();

        realRenderTime = m_timer.getTime().result();

        m_window->process(m_delta);
        m_window->handleInputs();
        m_window->handleBuffer();

        // Calculate the time it took to render the scene (including
        // frame rate adjustment), such that we can calculate the
        // delta time value.
        managedRenderTime = m_timer.getTime().result();
        m_delta = 1.0f / managedRenderTime.microsecs;

        // Report FPS every second
        if (fpsTimer.getTime().result().toSeconds() > 1.0) {
            fpsTimer.reset();
            notifyObservers(ObservationOf::FPS, {{"FPS", getFPS()}});
        }
    }

    m_timer.end();
    m_window->close();
}

ZEN::fps_int ZEN::Game::getFPS() const noexcept {
    return static_cast<fps_int>(std::floor(1.0f / getDeltaTime()));
}

ZEN::TimeMeasurement ZEN::Game::getRealRenderTime() const noexcept {
    return realRenderTime;
}

ZEN::dt_float ZEN::Game::getDeltaTime() const noexcept {
    return m_delta;
}

void ZEN::Game::requestExit() noexcept {
    keepOpen = false;
}
