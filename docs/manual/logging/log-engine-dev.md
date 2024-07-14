@page log-engine-dev Logging in engine development

## Library error

When ``ZEN_LIB_ERROR`` macro is a way for developers of the engine
to find implementation and design errors.

> **Example**:
> In the ZEN::OpenGL::Shader we map the engine-native enumerator
> ZEN::ShaderStage to corresponding GLAD definitions. Let's say
> a new stage is added to the enumerator in a future version,
> but never implement it in the OpenGL shader code.
> That's when we use this macro.
