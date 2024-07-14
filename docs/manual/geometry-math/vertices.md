@page vertices Vertices

A **vertex** is a part of a geometry. It's not strictly defined
what it contains, but it's usually a combination of:

- Position
- Normal, tangent and bi-tangent
- Color
- Texture coordinates

A vertex makes a single point in the game world, but that point
can &mdash; as seen above &mdash; comprise much more than just
position.

A point consists of a single vertex.
A line consists of two. A triangle consists of three.

In Zeronetics, you have ZEN::Vertex3D to build 3D shapes. The ``Vertex3D``
struct is used to pass information about shapes to @ref ZEN::IRenderer "renderers".
