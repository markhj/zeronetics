#include "zeronetics/game/game.h"

ZEN::Game::Game(const std::shared_ptr<IWindow> &window,
                const std::shared_ptr<IRenderer> &renderer) : m_window(window),
                                                              m_renderer(renderer) {
}

void ZEN::Game::run() {
    while (true) {
        // Game loop logic will be added here

        m_renderer->render();

        m_window->handleInputs();
        m_window->handleBuffer();
    }

    m_window->close();
}
