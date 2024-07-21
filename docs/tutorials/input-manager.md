@page input-manager Input Manager

To handle user inputs you need to implement an "Input Manager," and
connect it to the window instance.

There are a few ways to go about this, but at the heart of it, you can
either:

- Write a class which extends the contract ZEN::IInputManager,
  where you'll have to define all methods from the interface.
  This may require implementing methods you don't intend to use.
- Use the "shortcut", ZEN::BaseInputManager, where all methods
  are already implemented (but empty), and then override the ones
  you need.

Most use-cases suffice with option two, so that's the one we'll
go with.

Remember that you can see all required methods in the page about
ZEN::IInputManager.

## Example

In almost every game you need to manage key presses, so let's
look at that.

The basic implementation would be:

````cpp
class MyInputManager : public ZEN::BaseInputManager {
public:
    void onKeyStateChanged(const ZEN::KeyStateEvent &keyEvent) override {
        // ...
    }

};
````

However, at this point the method does nothing. It's empty.

You can explore ZEN::KeyStateEvent for learn about all the options,
but in the following example, we'll do "something" when the _A_-key
has just been pressed. Let's zoom in on the ``onKeyStateChanged`` method:

````cpp
void onKeyStateChanged(const ZEN::KeyStateEvent &keyEvent) override {
    if (keyEvent.key == ZEN::Key::A && keyEvent.keyState == ZEN::KeyState::JustPressed) {
        std::cout << "A was just pressed!" << std::endl;
    }
}
````

## Connecting to window

However, before your input manager is useful, it must be connected
to a ZEN::Window instance.

````cpp
auto myInputManager = std::make_shared<MyInputManager>(MyInputManager());

// Assuming Window has been set up

window->setInputManager(myInputManager);
````

From this point onwards, you should see the ``onKeyStateChanged`` method
get invoked when a key is pressed or released.

## See also

@ref control-systems
