@page setting-up-a-game Create a game

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
