@page fps FPS (frames per second)

One of the key metrics in game rendering that almost everyone
is familiar with is **FPS**, or **frames per second**.

## 💻 FPS

FPS is an expression of how well the hardware and the game's
code perform in unison. The higher the number, the better.

Essentially, it calculates how many frames the machine is able
to render per second.

To make sure objects move consistently across the screen, across
devices, it's important that you're familiar with @ref delta "delta time".

To retrieve the FPS, call ZEN::Game::getFPS.

````cpp
fps_int currentFPS = game.getFPS();
````

@note The ZEN::fps_int is a ``typedef`` defined in Zeronetics
to streamline use of integers for FPS calculations.

## ⌛ Real render time

However, FPS can &mdash; and often is &mdash; artificially
limited to match the monitor's frame rate, and thereby reduce
the risk of artifacts, such as "_screen tear_." It's therefore
not guaranteed to be a waterproof expression for how well your
code is performing.

When profiling &mdash; knowing how well your
game loop actually performs &mdash you might want to use
ZEN::Game::getRealRenderTime instead.

@note This function measures the time from the beginning of the
render loop and until the scene is fully rendered. But it
cuts off before the renderer swaps its buffer.
