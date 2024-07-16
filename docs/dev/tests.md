@page tests Test organization

The unit and feature testing suite is implemented with [C++ BBUnit](https://github.com/markhj/cpp-bbunit).

## 📘 Primary testing suite

The primary testing suite, located in the ``tests`` directory, performs tests on the main engine code.
Note that modules have individual, separate testing suites.

## 📚 Organization

Test cases are located in ``tests/src/cases/`` directory, and consists of a header and source file pair.

Tests from the main engine reside in the ``ZEN::Tests`` namespace.

