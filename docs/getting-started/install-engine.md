@page install-engine Install and build engine

The first step toward building a game with Zeronetics is to install
and build the engine.

The engine will be set up in a neutral location, and then referenced by
your game using an environment variable. But more about that in
@ref setting-up-a-game.

## ⤵️ Clone

@anchor install-engine-clone

First, navigate to where you want to install the engine,
and clone the source code.

````bash
git clone https://github.com/markhj/zeronetics
````

## 📦 Initializing submodules

@anchor install-engine-submodules

That was pretty easy, right? The next step isn't much harder.
Now, we initialize the Git submodules. In other words, we clone
the engine's dependencies.

````bash
git submodule init
git submodule update
````

## 🔨 Build

There's not a single way to build the engine because this depends
on your IDE or whether you use plain ``cmake``.

> Important: Preferably, you build the engine for both debug
> and release mode. That will make easier for you, as you're
> probably going to switch between the two when developing your
> game.

### Build guides

@subpage build-clion

## ▶️ And now?

Now where the engine is built and ready to use, you can continue
reading @ref setting-up-a-game.
