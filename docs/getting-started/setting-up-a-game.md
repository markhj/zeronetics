@page setting-up-a-game Create a game

@warning The engine is still a few features short of being
able to produce gameplay. Therefore, this article is incomplete.

This page assumes you've already
@ref install-engine "installed and built the engine".

## Environment variable

Step one is to make an environment variable visible to CMake.
This differs depending on IDE or whether you're using command-line
``cmake``.

The variable must be named ``ZERONETICS_DIR`` and contain the
path to where the engine is installed.

## CMake list

In your game's ``CMakeLists.txt`` file, you add:

````cmake
find_package(zeronetics REQUIRED)
````

Assuming your game executable is called ``MyGame``, you add
this line _after_ the ``add_executable`` directive.

````cmake
target_link_libraries(MyGame PRIVATE zeronetics module-1 module-2 module-3)
````

You need to explicitly include the Zeronetics modules you want to use.

They can be found here: @ref list-of-modules

> Important: If you already have a ``target_link_libraries``, you
> only need to append ``zeronetics`` and the modules there.
> Creating a second directive will cause problems.

## Creating the window

Now, let's review how to get a window on the screen. This is done in a
few steps:

- Create an instance of ZEN::Settings, which contains information about
  screen resolution, and other things relevant to generating the window.
- Create an instance of ZEN::Window.
- Generate a window with the settings.
- Create a ZEN::Game instance, and run it.

It would look something like this:

````cpp
#include <zeronetics/zeronetics.h>
#include <glfw-window/glfw-window.h>

int main() {
    ZEN::Settings settings;
    
    std::shared_ptr<ZEN::Window> window = std::make_shared<ZEN::Window>(ZEN::Window());
    window->windowTitle = "My Game";
    window->generate(settings);
    window->onClose([]() {
        std::exit(0);
    });

    ZEN::Game game(window);
    game.run();

    return 0;
}
````

Now, this just opens a blank window. But that means we've started off
correctly, and are ready to build an amazing game!
