@page engine-core-structure Core structure

To prevent circular dependencies, we've designed a clear hierarchy of
header inclusion and dependencies.

The hierarchy consists of four layers:

- Core
- Contracts
- Implementations and abstract classes
- Modules

Let's review them one by one.

## Core

Declarations of:

- Typedefs
- Macros
- Structs and classes which:
  - Have universal application and/or are general in nature
  - Have no dependencies, aside from other definitions in the same file

Examples include ``gw_float`` typedef, the ZEN::Settings struct and
ZEN::Version class. They have no dependencies on other parts of the engine.

The ``core`` is separated into fundamentals and second-level fundamentals.
The first layer consists of primitive declarations such as ``typedef``s
and simple macro definitions (e.g. build information).

The second-level fundamentals define structs, enums and classes at core-level.

## Contracts

Interfaces in the ``contracts`` directory are allowed to have dependencies
from ``core`` and other contracts.

Example: The ZEN::IWindow contract can depend on ZEN::IInputManager.

> Contracts must only have pure virtual functions. For abstract classes,
> see the next chapter.

## Implementations

Abstract classes and implementations of basic game engine logic exist
in this layer. They can depend on ``contracts``, ``core`` and other
files residing in the same directory.
They are not allowed to depend on files from other directories.

In other words, a class in ``controls`` can depend on files from
``core``, ``contracts`` and other files within ``controls``. But it
_cannot_ depend on files from ``game``, for example.

## Modules

Modules can extend and depend on any class or struct in the main
engine.

They are under no circumstances allowed to have dependencies
in other modules, and must be treated in total isolation from them,
making no assumptions about their existence or function.
