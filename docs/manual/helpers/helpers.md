@page helpers Helper functions

## 🔠 Strings

### Include

````cpp
#include <zeronetics/helpers/strings.h>
````

### To lower and upper-case

You can convert string to lower and uppercase using ZEN::toLowerCase
and ZEN::toUpperCase.

Example:

````cpp
std::string lowerCase = toLowerCase("Hello, World!");  // hello, world!
````

## Vertices

### Flatten vertex

To **flatten a vertex** basically means extracting its numeric values and
putting them into row on a vector. This has a number of applications,
among others it's useful for some renderers when they need to allocate data
on the GPU.

A list of @ref ZEN::VertexAttribute3D "vertex attributes" determine which
properties to extract and in which order.

See ZEN::Vertices::flattenVertex3D.

### Calculate normal

When given three points you can calculate the normal to the surface
they form in combination.

It's important that the points are given in **counter clock-wise
order**, otherwise the normal will point the opposite way of what's
expected.

To calculate a normal use ZEN::Vertices::calculateNormal:

````cpp
// Assuming Vec3 instances a, b and c have been defined already

Vec3 normal = ZEN::Vertices::calculateNormal(a, b, c);
````

