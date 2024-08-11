@page process-adv-lifecycle Advanced process life-cycles

In this chapter we take a look at more advanced and rare use-cases
of the process life-cycle management, namely the ability to pause,
resume and kill the process.

These actions are mainly needed in complex games, and in particular
to halt processing of expensive function calls.

@note These techniques are rarely needed for simpler games.

## ▶️ Pause and resume

A process can be paused and resumed using ZEN::Process::pause and
ZEN::Process::resume. They are executed directly on the process instance,
which means that in the edge cases where a process may be attached
to several processors, the effect is universal.

Assume we have:

````cpp
auto myProcess = std::make_shared<MyProcess>(MyProcess());

game.attach(myProcess);
````

At a time when you no longer need the process to actively run, you call

````cpp
myProcess.pause();
````

And when it's ready to run again:

````cpp
myProcess.resume();
````

## 💀 Killing a process

When you kill a process it remains attached, but stops processing and
cannot be resumed, even if you explicitly call the ``resume`` function.

````cpp
myProcess.kill();
````

It's relatively rare to need to kill a process rather than just
detaching it. Always aim to detach the processes, and only keep
killed/dangling processes attached, if somehow necessary.
