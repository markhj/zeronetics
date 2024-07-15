@page opengl-allocation Allocations in OpenGL

Allocation in our OpenGL is relatively straight-forward, but
it's worth noting that it has an auto-resize mechanism.

The allocation logic takes place mainly in ZEN::OpenGL::Renderer
and ZEN::OpenGL::VBO.

The VBO starts out with an initial size, but when it reaches
its capacity, it will be instructed by the renderer to double
its size.

When this happens all values on the ledger are wiped, and must
be re-inserted. In the same breath, all allocation addresses
stored in renderables are also remade, meaning that a renderable
may be stored at several addresses through-out its life-time
in the scene.

![](https://res.cloudinary.com/drfztvfdh/image/upload/v1721048758/zeronetics/OpenGL__VBO_Resizing_racdbr.png)

