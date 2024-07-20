@page control-systems-overview Control Systems

The **Control Systems** module provides a flexible system for managing
user inputs.

## 💡 The idea

The idea is that every user input gets mapped to a signal, and in a
completely separate process the signal is translated to an action.

![](https://res.cloudinary.com/drfztvfdh/image/upload/v1721452847/zeronetics/Contorl_mapping_-_Input_Mapping_1_m2hhmy.png)

For starters, this means that several inputs can map the same action
without the need of duplicate code. For example if Space Bar, primary mouse
button and Joystick "X" all make the character jump, then all
these inputs simply map to the "jump" signal, rather than each
implementing the action of jumping (or pointing to a part of the code
which makes the jump).

On the other side of the coin is a process which maps signals to actions.
This system doesn't know which user inputs were given, it just receives
the signal "jump", and decides what to do with it.

## 🎮 Basic usage

First, we instantiate ZEN::ControlSystems::ControlManager,
ZEN::ControlSystems::InputMapping and ZEN::ControlSystems::SignalHandler.

The ``ControlManager`` is the instance which will be passed to the
``ZEN::Window::setInputManager``. It's the "umbrella" class which binds
all the parts together.

````cpp
std::shared_ptr<ControlManager> controlManager = std::make_shared<ControlManager>(ControlManager());
std::shared_ptr<InputMapping> inputMapping = std::make_shared<InputMapping>(InputMapping());
std::shared_ptr<SignalHandler> signalHandler = std::make_shared<SignalHandler>(SignalHandler());
````

Next, we'll connect the ``InputMapping``
and ``SignalHandler`` to ``ControlManager``.

````cpp
controlManager->inputMapping = inputMapping;
controlManager->signalHandler = signalHandler;
````

And, finally, we need to instruct the ZEN::Window instance to use _this_
ZEN::IInputManager.

````cpp
window->setInputManager(controlManager);
````

## Simple m_mapping

In this example, we will map the press of the key ``A`` to the
signal ``left``.

````cpp
inputMapping->keyJustPressed(Key::A, "left");
````

And we'll instruct the ``SignalHandler`` to process the signal
``left`` by printing a message that says "Going left!".

````cpp
signalHandler->on("left", [&]() {
    std::cout << "Going left!" << std::endl;
});
````

And that's it! Now, when you open the game and press ``A```,
you will see "Going left!" printed to the console.

To learn more about the different m_mapping options, continue
reading @ref control-systems-m_mapping.

## 🔀 Swap mappings

Another advantage is that m_mapping and signal handling can get swapped
on-the-fly (during run-time). For example, when you open the main menu,
pause menu or a special HUD, you typically want to apply a completely
different set of controls.

This is achieved in the Control Systems module by swapping
the "in-game m_mapping" to the "main menu m_mapping", and so forth.

````cpp
auto inGameMapping = std::make_shared<InputMapping>(InputMapping());
auto mainMenuMapping = std::make_shared<InputMapping>(InputMapping());

// Code for when the game starts
controlManager->inputMapping = inGameMapping;

// When code is executed to open the main menu
controlManager->inputMapping = mainMenuMapping;
````

Of course, you can do the same with signal handling, but this is
normally not required, as long as your signals have proper naming.

Furthermore, by keeping the same signal handler through-out your
run-time, you have the benefit that in-game and main menu can share signals.
Maybe you always to be able to open a help menu, no matter if the player
is in the main menu or in-game.
