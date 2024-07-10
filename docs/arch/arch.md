@page arch Architecture

## 💫 Overview

The **Zeronetics** engine comprises the main engine code, and a number of modules.

The engine compiles to a static library which can be used by client applications
(i.e. games). The modules are built alongside the engine, also as static libraries.

The core contains functionality which is used across modules, and possibly also
in the games, such as I/O, math, interfaces, contracts, typedefs, and so forth.

Modules exist in complete isolation from other modules, but can freely depend
on anything contained in the core. This ensures modularity, making it easy
to swap components. For instance, switching from OpenGL to Vulkan should be
an easy "plug-and-play" from the game developer's perspective.

## 💖 Creating a new module

> Important: This is relevant for contributors to Zeronetics, or those
> working on forks of the engine.

If you want to create a new module for Zeronetics, the first step is to 
add a directory under ``modules``. Let's imagine a module called
``awesome``.

A module consists of a ``CMakeLists.txt``, and an ``include`` directory.
What happens after this is technically up to you, but the recommended structure
is as follows:

````text
modules/
└── awesome/
    ├── CMakeLists.txt
    ├── include/
    │   └── zeronetics/
    │       ├── awesome.h
    │       └── ...
    └── src/
        └── awesome.cpp

````

### CMake file

Within this directory, you must create a ``CMakeLists.txt`` which
will be included in the build system pipeline.

The basic format for a module's CMake is:

````cmake
cmake_minimum_required(VERSION 3.28)
project(awesome)

set(CMAKE_CXX_STANDARD 20)

add_library(awesome STATIC src/awesome.cpp)

# Optional: But makes it possible to include your
# header files without using relative paths with ..
target_include_directories(awesome PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
````

### Public headers

To make your module consumable by client apps (i.e. games), you add
a directory called ``include``. It's up to you to structure this directory,
but it's recommended to add header files in a subdirectory, to reduce
the risk of collisions in the client project.
Normally, the subdirectory would just be ``zeronetics``.

### Integrate in build process

To make the module part of the build process, you must add the module name
(``awesome``) to the list ``ZNE_MODULES`` found in ``cmake/modules-inc.cmake``.

````cmake
set(ZNE_MODULES
    # Other modules already registered
    awesome)
````

When you refresh your CMake configuration, the _Awesome_ module is now
part of the build process.
