@page observers Observers

The **observer pattern** implementation in Zeronetics uses

- ZEN::Observer: For classes which need to observe other objects
- ZEN::BeingObserved: For classes which can be observed

An example of this implementation is in ZEN::Game, where @ref fps "FPS"
is reported every few seconds to observers.

## 📌 Prerequisites

This article assumes fundamental knowledge of observer patterns.

## 🌐 Overview

Any number of classes can implement ZEN::BeingObserved, which exposes
a number of methods so other objects can "attach" and get notified
when notable events happen within the ``BeingObserved`` class.

When something of interest occurs, the extension of ``BeingObserved``
calls ``notifyObservers``.

It's the class which implements ``BeingObserved`` which is responsible
for picking out the points that should trigger such notifications.

![](https://res.cloudinary.com/drfztvfdh/image/upload/v1721449501/zeronetics/Observer_pattern_porw1e.png)

Every attached observer will then be notified via their individual
implementations of ZEN::Observer::notify.

@note Example:
A window instance may want to re-generate when video settings change.
In this case the window class is the observer, and settings is
"being observed". The settings class will notify its observers,
among them window, when the settings are updated.

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
