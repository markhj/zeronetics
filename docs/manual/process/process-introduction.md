@page process-introduction Introduction to processes

A @ref ZEN::Process "process" is any class which inherits ``ZEN::Process``.
Any such class can be attached to the @ref game-loop "game loop", and it
can literally entail anything from a simple timer over physics computation
to the main character.

## 🍂 Life cycle

A process can theoretically be attached to any number of
@ref ZEN::Processor "processors", but in most use-cases that's just the
primary @ref game-loop "game loop".

When a process is attached to a processor it becomes active, and starts
executing its functionality. Underway, it can be paused, killed or detached,
which has different effects and consequences.

For more information, please read @ref process-lifecycle.

## 📲 Implementation

To implement a new process class, you extend ZEN::Process. In theory,
you don't have to do anything else, but your process won't do anything.
You will in most cases need to implement both or one of
@ref ZEN::Process::onReady onReady and/or
@ref ZEN::Process::onProcess onProcess.

In a limited set of use-cases, you may want to do some additional
processing when the class is attached and detached. If not, you can
leave those functions out.

````cpp
class MyProcess : public ZEN::Process {
public:
    void onAttach() override {
        
    }
    
    void onDetach() override {
        
    }

protected:
    void onReady() override {
        
    }
    
    void onProcess(dt_float delta) override {
        
    }
````

## 💫 Usage

Assuming you've created a ZEN::Game instance (or another process
handler), then you attach it to the process this way:

````cpp
auto myProcess = std::make_shared<MyProcess>(MyProcess());

game.attach(myProcess);
````

If needed, the process can be detached using ZEN::Processor::detach.

````cpp
game.detach(process);
````

And that's all. Doing this will attach a process to the game loop.

## See also

@ref process-lifecycle
