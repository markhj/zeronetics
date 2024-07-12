@page build-info Build information

When you've included ``zeronetics/core/build.h``, you get access to a range
of macros which are useful, when you want to alter your
code flow depending on whether it's debug or release build.

## Macros

| Macro          | Description                                 |
|----------------|---------------------------------------------|
| ``IS_DEBUG``   | Is true, when the build is in debug mode.   |
| ``IS_RELEASE`` | Is true, when the build is in release mode. |

## Example

````cpp
#include "zeronetics/core/build.h"

#if IS_DEBUG
// Do something debug-specific
#endif
````

## Note

You can theoretically also use it in-code:

````cpp
if (IS_DEBUG) {
    // ...
}
````

But this may upset your IDE, because IDEs often evaluate according
to the current build information, meaning that your IDE's idea of what
``IS_DEBUG`` is, is static. It will therefore show a warning on the statement,
because, as far as the IDE knows, the value isn't subject to change, and
can be simplified (i.e. removed).
