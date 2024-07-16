@page delta Delta time

## 💀 The problem

Imagine the following scenario within the game loop:

The player holds down the _W_-key to move the camera forward.
Your code moves it ``0.1`` _per frame_.

But what happens on a slow machine which can only render 40 frames
per second versus a machine that can easily render 200?

On the strong machine the camera moves much further per second.
And that's not what we want. We want objects to move _consistently_
across the screen regardless of how many frames per second are rendered.

@note For the record, great variation in frames per second can
also happen on the _same_ machine.

## 💡 The solution

**Delta time** is a measurement of the varying interval between
two frames. And it's an essential part of game programming.

@note Delta is not a fixed value, and it normally changes &mdash;
now and then dramatically &mdash; between two frames.

Normally, game engines provide you the delta  value, and that's
also the case in Zeronetics.

To use the delta value, you multiply your "speed per second"
with the delta value.

Back to our example from before: To make the camera move at the
apparent same speed between two machines (or the same machine
with varying FPS), we first decide that we want the camera to
move ``2.0`` per second. Then, in every frame, while the _W_-key
is down, we simply say:

````cpp
camera.position.z += delta * 2.0;
````

## See also

@ref fps
