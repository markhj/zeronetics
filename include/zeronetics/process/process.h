#pragma once

#include "zeronetics/core/enums.h"
#include "zeronetics/core/typedefs.h"
#include "zeronetics/traits/has-unique-id.h"

namespace ZEN {
    /**
     * Objects inheriting Process can be attached to the game loop.
     *
     * @ref process
     */
    class Process : public HasUniqueId {
    public:
        /**
         * Start this process instance.
         *
         * @ref process-lifecycle
         */
        void start() noexcept;

        /**
         * Pause this process.
         *
         * @note Will throw a warning if not in active state.
         *
         * @ref process-lifecycle
         * @ref process-adv-lifecycle
         */
        void pause() noexcept;

        /**
         * Resumt this process.
         *
         * @note Will throw a warning if not in paused state.
         *
         * @ref process-lifecycle
         * @ref process-adv-lifecycle
         */
        void resume() noexcept;

        /**
         * Kill the instance.
         *
         * @note It will remain attached, but is no longer active
         *      and cannot be resumed. It's advisable to remove killed
         *      processes whenever it's possible.
         *
         * @ref process-lifecycle
         * @ref process-adv-lifecycle
         */
        void kill() noexcept;

        /**
         * Event for when the process has been attached to a new ZEN::Processor.
         *
         * @ref process-lifecycle
         */
        virtual void onAttach();

        /**
         * Event for when the process is detached from a manager.
         *
         * @ref process-lifecycle
         */
        virtual void onDetach();

        /**
         * Generalized process call.
         *
         * @ref process-lifecycle
         *
         * @param delta
         */
        void process(dt_float delta);

        /**
         * Get the current process state.
         *
         * @return
         */
        [[nodiscard]] ProcessState getProcessState() const noexcept;

    protected:
        /**
         * Event executed just before the first processing of the instance.
         *
         * @ref process-lifecycle
         */
        virtual void onReady();

        /**
         * What should happen while the process is active.
         * This function will be called on every frame (game loop iteration).
         *
         * @ref process-lifecycle
         *
         * @param delta
         */
        virtual void onProcess(dt_float delta);

    private:
        /**
         * Current state of the process.
         *
         * @ref process-lifecycle
         */
        ProcessState m_processState = ProcessState::Pending;

    };
}
