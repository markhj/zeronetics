#pragma once

#include "zeronetics/contracts/window.h"
#include "zeronetics/contracts/renderer.h"
#include <memory>

namespace ZEN {
    /**
     * The main game class which connects different components,
     * such as window and renderer, and maintains the game loop.
     */
    class Game {
    public:
        /**
         * Construct instance.
         *
         * @param window
         */
        Game(const std::shared_ptr<IWindow> &window,
             const std::shared_ptr<IRenderer> &renderer);

        /**
         * Run the game loop.
         */
        void run();

    private:
        std::shared_ptr<IWindow> m_window;

        std::shared_ptr<IRenderer> m_renderer;

    };
};
