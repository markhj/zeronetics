@page render-manager Understanding render management

@warning This documentation is potentially not up-to-date,
as refactoring of involving this component is currently taking place.

In Zeronetics, there's loose coupling between the renderer (e.g.
@ref opengl "OpenGL") and the logic which manages objects.

The gap between the two is filled with an implementation of
ZEN::IRenderManager.

## 🎨 What is a render manager?

The purpose of the render manager is to **facilitate two-way
communication** between the objects you want to render and
the renderer.

When an object moves 10 pixels to the left, the object will not
itself directly communicate this change to the renderer. Instead,
it will communicate to the render manager, which is
then responsible for communicating with the renderer.

In practice, the render manager receives
@ref ZEN::IRendererRequests "requests". For instance, if
a new object has been added to the scene, the request
will basically say "please, allocate this object."

Similarly, if the object is removed, the request will say
"please, de-allocate me," and if it has changed, it would
translate to: "I have changed, update my data".

![](https://res.cloudinary.com/drfztvfdh/image/upload/v1721036345/zeronetics/Render_manager_flow_z6tszr.png)

The Render Manager itself has no actual authority, instead
it's continually managed by the "scene" and the renderer.

@note It's up to the renderer implementation to manage
these requests. For more in-depth information on _why_ this is,
you can read @ref arch-render-manager.

## 🎥 The "scene"

It's intentional that we haven't been super-specific about
"what" is controlling the objects.

This has to do with the loose coupling and design choices
in Zeronetics, where we desire to make it possible to swap
all the moving parts.

In that manner, you can use built-in classes to manage the scene,
write your own, or &mdash; although not recommended &mdash; have
no explicit management.
