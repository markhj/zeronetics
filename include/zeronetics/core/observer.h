#pragma once

#include <vector>
#include <memory>
#include <variant>
#include <unordered_map>

namespace ZEN {
    typedef std::variant<int, std::string> observable_types;
    typedef std::unordered_map<std::string, observable_types> observer_meta;

    struct ObserverMeta : public observer_meta {
    public:
        using observer_meta::unordered_map;
    };

    class BeingObserved;

    /**
     * The category that is being observed.
     *
     * For non-native observation, you can use ``Custom``.
     *
     * @ref observers
     */
    enum class ObservationOf {
        Custom,
        FPS,
    };

    /**
     * The "message" that is passed from the subject to the observer,
     * when a new observable event has happened.
     *
     * @ref observers
     */
    struct Observation {
        /**
         * The "category" of observation.
         */
        ObservationOf of = ObservationOf::Custom;

        /**
         * Optional set of meta data provided by the subject.
         */
        ObserverMeta meta;
    };

    /**
     * The interface for classes which can be notified of changes
     * in a subject class.
     *
     * @ref observers
     */
    class Observer {
    public:
        /**
         * Notify the implementation class of a new observation
         * event.
         *
         * @param observation
         */
        virtual void notify(const Observation &observation) = 0;

    };

    /**
     * Implemented by classes which can be observed.
     *
     * @ref observers
     */
    class BeingObserved {
    public:
        /**
         * Attach a new observer which will be notified upon new observable
         * events.
         *
         * @param observer
         */
        void attachObserver(const std::shared_ptr<Observer> &observer) noexcept;

    protected:
        /**
         * When a noteworthy event has happened within the implementation class
         * this method is used to notify the attached observers.
         *
         * @param observation
         */
        void notifyObservers(ObservationOf of,
                             const ObserverMeta &meta) const;

        /**
         * Notify observers without any meta data.
         *
         * @param of
         */
        void notifyObservers(ObservationOf of) const;

    private:
        /**
         * List of attached observers.
         */
        std::vector<std::shared_ptr<Observer>> m_observers;
    };
}
