#include "zeronetics/game/game.h"
#include <chrono>
#include <iostream>

ZEN::Game::Game(const std::shared_ptr<IWindow> &window,
                const std::shared_ptr<IRenderer> &renderer) : m_window(window),
                                                              m_renderer(renderer) {
}

void ZEN::Game::run() {
    if (!m_renderer->isInitialized()) {
        m_renderer->initialize();
    }

    while (true) {
        auto start = std::chrono::high_resolution_clock::now();

        m_renderer->clear();

        m_renderer->render();

        realRenderTime = std::chrono::duration_cast<std::chrono::microseconds>(
                                 std::chrono::high_resolution_clock::now() - start)
                                 .count();

        m_window->handleInputs();
        m_window->handleBuffer();

        managedRenderTime = std::chrono::duration_cast<std::chrono::microseconds>(
                             std::chrono::high_resolution_clock::now() - start)
                             .count();
    }

    m_window->close();
}

ZEN::fps_int ZEN::Game::getFPS() const noexcept {
    return static_cast<fps_int>(floor(1000000.0 / managedRenderTime));
}

ZEN::render_time_microsecs ZEN::Game::getRealRenderTime() const noexcept {
    return realRenderTime;
}
