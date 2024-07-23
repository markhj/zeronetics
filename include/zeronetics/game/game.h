#pragma once

#include "zeronetics/contracts/renderer.h"
#include "zeronetics/contracts/window.h"
#include "zeronetics/core/timer.h"
#include "zeronetics/core/observer.h"
#include <memory>

namespace ZEN {
    /**
     * The main game class which connects different components,
     * such as window and renderer, and maintains the game loop.
     */
    class Game : public BeingObserved {
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
         * Loop function which should be implemented by the game.
         *
         * @param delta
         */
        virtual void loop(dt_float delta) = 0;

        /**
         * Retrieve current delta time value.
         *
         * @note Is 0.0 during rendering of the first frame.
         *
         * @ref delta
         *
         * @return
         */
        [[nodiscard]] dt_float getDeltaTime() const noexcept;

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

        /**
         * Request the end the game loop.
         */
        void requestExit() noexcept;

    private:
        /**
         * Indicates when to exit the game loop.
         */
        bool keepOpen = true;

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
         * Current delta time.
         */
        dt_float m_delta = 0.0;

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
