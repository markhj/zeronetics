#include "zeronetics/core/observer.h"


void ZEN::BeingObserved::attachObserver(const std::shared_ptr<Observer> &observer) noexcept {
    m_observers.emplace_back(observer);
}

void ZEN::BeingObserved::notifyObservers(ZEN::ObservationOf of) const {
    notifyObservers(of, {});
}

void ZEN::BeingObserved::notifyObservers(ZEN::ObservationOf of, const ZEN::ObserverMeta &meta) const {
    Observation observation{
            .of = of,
            .meta = meta,
    };
    for (const std::shared_ptr<Observer> &observer: m_observers) {
        observer->notify(observation);
    }
}
