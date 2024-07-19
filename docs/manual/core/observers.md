@page observers Observers

The **observer pattern** implementation in Zeronetics uses

- ZEN::Observer: For classes which need to observe other objects
- ZEN::BeingObserved: For classes which can be observed

An example of this implementation is in ZEN::Game, where @ref fps "FPS"
is reported every few seconds to observers.
