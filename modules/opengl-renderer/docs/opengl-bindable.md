@page opengl-bindable OpenGL context

When working with the OpenGL module, you often work with bindable
contexts (VAO, VBO, shaders, framebuffers, textures, etc.).
To ease this work you can use the ZEN::OpenGL::StdBinding.

## An example

Let's review the shader to get an understanding. The ZEN::OpenGL::Shader
extends ``ZEN::OpenGL::StdBinding<gl_uint>``.

This provides basic binding functionality, but you have to implement
a few functions on your own, which are specific to each context.

````cpp
class NewContext : public ZEN::OpenGL::StdBinding<gl_uint> {
public:
    void bindTo(T context) override;
    [[nodiscard]] T getContextId() const override;

protected:
    [[nodiscard]] std::optional<T> getCurrentContextId() const override;
};
````

For the shader &mdash; again, as an example &mdash; the methods are
implemented like this:

````cpp
void ZEN::OpenGL::Shader::bindTo(gl_uint context) {
    glUseProgram(context);
}

std::optional<ZEN::OpenGL::gl_uint> ZEN::OpenGL::Shader::getCurrentContextId() const {
    GLint currentProgram = 0;
    glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
    return currentProgram;
}
````

## Functions

### Short-hand for binding

You bind to a context with ``bind``.

````cpp
myShader->bind();
````

And unbind:

````cpp
myShader->unbind();
````

### With

ZEN::OpenGL::StdBinding provides a series of useful functions.
Most importantly, the ``with`` function, which safely enters
and leaves a context. By "safely," is meant that if another context
was bound by the time ``with`` is called, the flow is returned
to that context after ``with``.

````cpp
shader1->bind();
// Shader 1 is now active

shader2->with([&]() {
    // Shader 2 is active within this scope
});

// Shader 1 is once again active (without needing an explicit call)
````
