@page control-systems-m_mapping Input m_mapping

In this article, we're going to review the various types of 
input m_mapping you can do with ZEN::ControlSystems::InputMapping.

## Key pressed and released

To map when a key has just been pressed, or just released, use 
these methods:

````cpp
inputMapping->keyJustPressed(Key::W, "start_running_forward");
inputMapping->keyJustReleased(Key::W, "stop_running_forward");
````
