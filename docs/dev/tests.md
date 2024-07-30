@page tests Test organization

The unit and feature testing suite is implemented with [C++ BBUnit](https://github.com/markhj/cpp-bbunit).

## 📘 Primary testing suite

The primary testing suite, located in the ``tests`` directory, performs tests
on the main engine code. Note that modules have individual, separate
testing suites.

## 📚 Organization

Test cases are located in the ``tests/src/cases/`` directory, and consists of
a header and source file pair.

Tests from the main engine reside in the ``ZEN::Tests`` namespace.

## 📦 Payloads

The directory ``tests/payloads`` contains data files which can be read by the
test cases. It is copied to the build directory when CMake refreshes.

@note Copying the directory is necessary, because the built executable
reads relative paths from its new home.

A test case is allowed to manipulate content within its assigned payload
directory.

@important The directory is not rebuilt upon re-running C++ BBUnit. The
directory is managed by CMake. If a test run manipulates contents during
run-time, and the second run has certain expectations, you may see your
test cases fail. Make sure to account for this. In most cases, it suffices
to have files which are treated as static, and others as dynamic.
