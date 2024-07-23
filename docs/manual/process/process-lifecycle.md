@page process-lifecycle Life-cycle of a process

## 🐣 Basic life-cycle

A @ref ZEN::Process "process" can live for any time outside a processor.

One attached to a processor ZEN::Process::onAttach is called. This
function is not so frequently needed though.

When the process reaches the first time it's about to be processed,
ZEN::Process::onReady is called. This is where you'll want to prepare
the instance by initializing its various states, if that hasn't already
been done.

![](https://res.cloudinary.com/drfztvfdh/image/upload/v1721741480/zeronetics/Process_life-cycle_ldtaex.png)

After this point, ZEN::Process::onProcess is called an unknown number of times.
Basically, for as long as the game loop lives or until the process is 
detached from the processor.

When manually detached (for example upon scene change), ZEN::Process::detach
is invoked.

## 📜 See also

@ref process-adv-lifecycle
