@page control-systems-mapping Input mapping

In this article, we're going to review the various types of 
input mapping you can do with ZEN::ControlSystems::InputMapping.

## Key pressed and released

To map when a key has just been pressed, or just released, use 
these methods:

````cpp
inputMapping->keyJustPressed(Key::W, "start_running_forward");
inputMapping->keyJustReleased(Key::W, "stop_running_forward");
````

## Key down

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
