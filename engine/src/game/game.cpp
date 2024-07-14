#include "zeronetics/game/game.h"

ZEN::Game::Game(const std::shared_ptr<IWindow> &window,
                const std::shared_ptr<IRenderer> &renderer) : m_window(window),
                                                              m_renderer(renderer) {
}

void ZEN::Game::run() {
    if (!m_renderer->isInitialized()) {
        m_renderer->initialize();
    }

    while (true) {
        m_renderer->clear();

        m_renderer->render();

        m_window->handleInputs();
        m_window->handleBuffer();
    }

    m_window->close();
}
