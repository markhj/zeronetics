@page geometry-relationships Geometry relationships

This page briefly touches on the relationship between
@ref vertices "vertices", @ref shapes "shapes" and meshes.

## 🔢 Meshes and vertices

A mesh &mdash; which is one way to visualize objects in a scene &mdash;
consists of @ref vertices "vertices".

@note A vertex is a single point with a position, and a set of optional
properties such as normal, tangent, color, texture coordinates, etc.

These points are, in a typical rendering context, used to form triangles.
A few, tens, hundreds or thousands of triangles make up the shapes you
see on-screen.

## 🔷 Shapes

**Shapes** are not a required part of forming meshes, but they are there
to ease the process of building commonly used shapes, such as
@ref ZEN::Cube "cubes".

To put it into perspective: A simple shape like a cube requires 12 triangles
(2 for each of the six sides). Explicitly defining these 12 triangles for
every cube is very cumbersome. Instead, you have the
ZEN::Cube "cube shape", and an array of other shapes.

@note You can build your own re-usable shapes by extending ZEN::Shape3D.
