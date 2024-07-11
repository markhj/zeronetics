@page mouse Handling the mouse

## Prerequisites

Before reading this article, you must read:

@ref input-manager

## Mouse movement

Whenever the mouse moves within the window, it triggers an event.
When the mouse is outside the window, or completely still, there
will be no event reporting.

To listen to mouse movements, add content to the
ZEN::IInputManager::onMouseMoved method.

````cpp
class MyInputManager : public ZEN::BaseInputManager {
public:
    void onMouseMoved(const MouseMovedEvent &mouseMovedEvent) override {
        // ...
    }

};
````

The ZEN::MouseMovedEvent reports the current position of the cursor
(relative to the window, meaning that ``0, 0`` is the top-left corner
of the frame).

But it also provides a ``relative`` property, which indicates the movement
since last event reporting.

To see it in effect, you could do something like:

````cpp
void onMouseMoved(const MouseMovedEvent &mouseMovedEvent) override {
    std::cout << mouseMovedEvent.relative.x << ", " << mouseMovedEvent.relative.y << "\n";
}
````
