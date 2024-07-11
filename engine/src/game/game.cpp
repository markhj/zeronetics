#include "zeronetics/game/game.h"
#include <iostream>


ZEN::Game::Game(const std::shared_ptr<IWindow> &window) : m_window(window) {

}

void ZEN::Game::run() {
    while (true) {
        // Game loop logic will be added here

        m_window->handleInputs();
        m_window->handleBuffer();
    }

    m_window->close();
}
