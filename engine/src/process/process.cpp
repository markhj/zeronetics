#include "zeronetics/process/process.h"
#include "zeronetics/logging/logging.h"
#include <format>


void ZEN::Process::onAttach() {
}

void ZEN::Process::onDetach() {
}

void ZEN::Process::onReady() {
}

void ZEN::Process::process(ZEN::dt_float delta) {
    if (m_processState != ProcessState::Active) {
        return;
    }

    onProcess(delta);
}

ZEN::ProcessState ZEN::Process::getProcessState() const noexcept {
    return m_processState;
}

void ZEN::Process::start() noexcept {
    if (m_processState != ProcessState::Pending) {
        ZEN_WARN(std::format("Can only start a pending process. Process {} is not pending.", getUniqueId()),
                 LogCategory::Process);
        return;
    }

    onReady();
    m_processState = ProcessState::Active;
}

void ZEN::Process::pause() noexcept {
    if (m_processState != ProcessState::Active) {
        ZEN_WARN(std::format("Can only pause a running process. Process {} is not running.", getUniqueId()),
                 LogCategory::Process);
        return;
    }

    m_processState = ProcessState::Paused;
}

void ZEN::Process::resume() noexcept {
    if (m_processState != ProcessState::Active) {
        ZEN_WARN(std::format("Can only resume a paused process. Process {} is not paused.", getUniqueId()),
                 LogCategory::Process);
        return;
    }

    m_processState = ProcessState::Active;
}

void ZEN::Process::kill() noexcept {
    m_processState = ProcessState::Killed;
}

void ZEN::Process::onProcess(ZEN::dt_float delta) {
}
