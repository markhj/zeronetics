@page observers Observers

The **observer pattern** implementation in Zeronetics uses

- ZEN::Observer: For classes which need to observe other objects
- ZEN::BeingObserved: For classes which can be observed

An example of this implementation is in ZEN::Game, where @ref fps "FPS"
is reported every few seconds to observers.

## 📌 Prerequisites

This article assumes fundamental knowledge of observer patterns.

## 🌘 Implementing an observable

Creating a class that can be observed by other classes involves
extending ZEN::BeingObserved.

At the point in the code flow where you want to notify observers,
you call ZEN::BeingObserved::notifyObservers.

````cpp
class ObjectWithImportantInformation : public BeingObserved {
public:
    void somethingHappens() {
        notifyObservers(ObservingOf::SettingsChanged);
    }
    
};
````

When ``notifyObservers`` is called all attached observers will be
notified.

But wait, "attached observers"? Yes, you need to attach observers to
instances of ``ObjectWithImportantInformation``. This is done using:

````cpp
ObjectWithImportantInformation observableInstance;
observableInstance.attachObserver(observer1);
observableInstance.attachObserver(observer2);
````

## 🔭 Implementing an observer

Creating a class which can be observed involves extending ZEN::Observer,
and implementing the function ZEN::Observer::notify virtual method.

````cpp
class MyClass : public Observer {
public:
    void notify(const Observation &observation) override {
        // Do something upon being notified 
    }
};
````

Instances of ``MyClass`` can be attached to instances of ZEN::BeingObserved,
for example ZEN::Game.

````cpp
std::shared_ptr<MyClass> myClass = std::make_shared<MyClass>(MyClass());

game.attachObserver(myClass);
````

## Meta data

The ZEN::Observation which represents the "message" between an  
observable object and its observers can contain meta data.

Example from ZEN::Game class:

````cpp
notifyObservers(ObservationOf::FPS, {{"FPS", currentFps}});
````
