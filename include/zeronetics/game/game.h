#pragma once

#include "zeronetics/contracts/contracts.h"
#include <memory>

namespace ZEN {
    class Game {
    public:
        Game(const std::shared_ptr<IWindow> &window);

        void run();

    private:
        std::shared_ptr<IWindow> m_window;
    };
};
