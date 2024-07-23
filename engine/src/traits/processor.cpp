#include "zeronetics/traits/processor.h"

#include <algorithm>

bool ZEN::Processor::isAttached(const std::shared_ptr<Process> &process) const noexcept {
    auto it = std::find_if(m_processList.begin(),
                           m_processList.end(),
                           [&](const std::shared_ptr<Process> &other) -> bool {
                               return other->getUniqueId() == process->getUniqueId();
                           });

    return it != m_processList.end();
}

void ZEN::Processor::attach(const std::shared_ptr<Process> &process) noexcept {
    if (isAttached(process)) {
        return;
    }
    m_processList.emplace_back(process);
    process->onAttach();
}

void ZEN::Processor::detach(const std::shared_ptr<Process> &process) noexcept {
    auto it = std::find_if(m_processList.begin(),
                           m_processList.end(),
                           [&](const std::shared_ptr<Process> &other) -> bool {
                               return other->getUniqueId() == process->getUniqueId();
                           });

    if (it != m_processList.end()) {
        m_processList.erase(it);
        process->onDetach();
    }
}

void ZEN::Processor::processAll(dt_float delta) {
    std::for_each(m_processList.begin(),
                  m_processList.end(),
                  [&](const std::shared_ptr<Process> &item) {
                      if (item->getProcessState() == ProcessState::Pending) {
                          item->start();
                      }
                      item->process(delta);
                  });
}
