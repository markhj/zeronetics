#pragma once

#include "zeronetics/process/process.h"
#include <memory>
#include <vector>

namespace ZEN {
    /**
     * Trait used for attaching, detaching, processing and general
     * management of ZEN::Process.
     *
     * @ref process
     */
    class Processor {
    public:
        /**
         * Returns true, if the process instance is currently attached to this object.
         *
         * @param process
         * @return
         */
        [[nodiscard]] bool isAttached(const std::shared_ptr<Process> &process) const noexcept;

        /**
         * Attach a process to this object.
         *
         * @param process
         */
        void attach(const std::shared_ptr<Process> &process) noexcept;

        /**
         * Detach process from this object.
         *
         * @param process
         */
        void detach(const std::shared_ptr<Process> &process) noexcept;

    protected:
        /**
         * Compute all contained processes.
         *
         * @param delta
         */
        void processAll(dt_float delta);

    private:
        /**
         * List of processes.
         */
        std::vector<std::shared_ptr<Process>> m_processList;

    };
}
