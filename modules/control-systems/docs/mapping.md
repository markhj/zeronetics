@page control-systems-mapping Input mapping

In this article, we're going to review the various types of 
input mapping you can do with ZEN::ControlSystems::InputMapping.

## 🆗 Keyboard

### Key pressed and released

To map when a key has just been pressed, or just released, use 
these methods:

````cpp
inputMapping->keyJustPressed(Key::W, "start_running_forward");
inputMapping->keyJustReleased(Key::W, "stop_running_forward");
````

Available keys can be seen on ZEN::Key enumerator.

### Key down

While you're holding down a key, you can use:

````cpp
inputMapping->keyDown(Key::W, "moving_forward");
````

The corresponding signal handler _can_ use delta value:

````cpp
signalHandler->on("forward", [&](dt_float delta) {
    character->position.z -= 2.0f * delta;
});
````

## 🐀 Mouse

### Mouse button clicked and released

In a fashion eerily similar to the keyboard, you can track when
the mouse button is first clicked and when it's released.

````cpp
inputMapping->mouseButtonJustClicked(MouseButton::PrimaryMouseButton, "start_shooting");
inputMapping->mouseButtonJustReleased(MouseButton::PrimaryMouseButton, "stop_shooting");
````

Available buttons can be seen on ZEN::MouseButton.

### Mouse button down

You can signal when a mouse button is held down using ``mouseButtonDown``:

````cpp
inputMapping->mouseButtonDown(MouseButton::PrimaryMouseButton, "fly");
````
