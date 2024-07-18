#pragma once

#include "zeronetics/contracts/renderer.h"
#include "zeronetics/contracts/window.h"
#include "zeronetics/core/timer.h"
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

        /**
         * Retrieve current FPS (frames per second).
         *
         * @ref fps
         *
         * @return
         */
        [[nodiscard]] fps_int getFPS() const noexcept;

        /**
         * Returns the "real render time", which is the time it has actually
         * taken for your code to render a frame. In other words, this is useful
         * for profiling, since the delta value (FPS) can be impacted
         * by an intentional mechanism to synchronise the frames per second with
         * the monitor's frame rate.
         *
         * @ref fps
         *
         * @return
         */
        [[nodiscard]] TimeMeasurement getRealRenderTime() const noexcept;

    private:
        /**
         * Window instance.
         */
        std::shared_ptr<IWindow> m_window;

        /**
         * Timer for measuring delta and rendering time
         */
        Timer m_timer;

        /**
         * Renderer of choice.
         */
        std::shared_ptr<IRenderer> m_renderer;

        /**
         * Time between two frames are rendered given in microseconds.
         *
         * You can use this to calculate the delta value.
         *
         * @note This duration may be "artificially" impacted by
         *      mechanisms aiming for the monitor's frame rate.
         *
         * @ref delta
         */
        TimeMeasurement managedRenderTime;

        /**
         * The real time it took to render a frame (given in microseconds).
         *
         * Can be used for profiling.
         *
         * @note You shouldn't use this to calculate FPS (frames per
         *      second), because the impact of frame rate adjustment
         *      mechanisms isn't accounted for. Use ``renderTime``
         *      to calculate FPS.
         */
        TimeMeasurement realRenderTime;

    };
};
