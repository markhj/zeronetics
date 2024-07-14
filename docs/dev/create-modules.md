@page create-modules Creating new modules

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
(``awesome``) to the list ``ZEN_MODULES`` found in ``cmake/modules-inc.cmake``.

````cmake
set(ZEN_MODULES
    # Other modules already registered
    awesome)
````

If your library depends on vendor (third-party) libraries, you must also
define those.

You specify them in a list in CMake, named ``LIBS_<NAME>``, where ``<NAME>``
is your library written in uppercase, and with hyphens replaced with underscores.

Example:

````cmake
set(LIBS_AWESOME glfw3)
````

When you refresh your CMake configuration, the _Awesome_ module is now
part of the build process.

## Namespace

For modules, the choice of namespace is relatively free choice.

However, as long as a module has any dependencies from the main engine,
it's recommended to nest the module within ``ZEN`` namespace. This is
to make it clear that the module (probably) can't just be get unplugged
from Zeronetics and applied in other projects.

Larger modules, especially those with risk of name collisions, should
be nested within their own namespace.

Our OpenGL module, for example, resides in ``ZEN::OpenGL``. This is
to avoid collisions of common names such as ``Shader`` and ``Renderer``
which is likely to exist in other modules.
