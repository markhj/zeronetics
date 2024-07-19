#include "zeronetics/game/game.h"
#include <chrono>

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

    while (true) {
        m_timer.reset();

        m_renderer->clear();

        m_renderer->render();

        realRenderTime = m_timer.getTime().result();

        m_window->handleInputs();
        m_window->handleBuffer();

        managedRenderTime = m_timer.getTime().result();

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
    return static_cast<fps_int>(floor(1000000.0 / managedRenderTime.microsecs));
}

ZEN::TimeMeasurement ZEN::Game::getRealRenderTime() const noexcept {
    return realRenderTime;
}
