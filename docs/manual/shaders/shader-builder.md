@page shader-builder Shader Builder

A **Shader Builder** is a class (based on @ref ZEN::IShaderBuilder "a contract") which
compiles basic shaders for a specific @ref ZEN::IRenderer "renderer".

Their purpose is to ease creation of basic shader use-cases, as well as constructing
them from data files, such as HXL.

They work by taking a set of @ref ZEN::VertexAttribute "vertex attributes", and
various instructions, for instance @ref ZEN::Projection "projection" and
@ref lights-tutorial "lighting".

## Shader builders

@ref glsl-shader-builder
