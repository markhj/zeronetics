@page render-groups Render groups

## 🔠 What is a render group?

A **render group** is a collection of renderable objects and
a shader. Render groups are mainly used in the
@ref render-manager "render manager" to structure the render
flow.

The idea is that objects which anyway need to use the same
shader are grouped together, such that the shader only need to
be activated _once_. If the renderables weren't organized in
groups you'd end up activating the same shader ten times,
if there were ten renderables.

![](https://res.cloudinary.com/drfztvfdh/image/upload/v1721036992/zeronetics/Render_groups_lqydnc.png)

As you can see, if we rendered objects in the order they were
provided, we'd have fragmented structure, where every shader
would need to be activated several times.

@note Render groups open up for more opportunities for performance
optimization, in the future.

## 🚧 Working with groups

To create a render group, you instantiate a ZEN::RenderGroup3D,
connect it with a shader and add renderables.

Groups should be created as shared pointers to be usable with
ZEN::RenderManager.

````cpp
std::shared_ptr<RenderGroup3D> myGroup = std::make_shared<RenderGroup3D>(RenderGroup3D());
myGroup->shader = someShader;
myGroup->renderables3d.push_back(object1);
myGroup->renderables3d.push_back(object4);
myGroup->renderables3d.push_back(object6);
````

@warning If you don't connect a shader, the group will be
skipped during rendering.

And last, the group must be added to your render manager.

````cpp
renderManager->renderGroups3d.push_back(myGroup);
````

## 🔵 Primitive types

You can decide whether a group should be rendered as points, lines
or triangles.

````cpp
myGroup->drawPrimitive = DrawPrimitive::Lines;
````

The value can be set as an option from ZEN::DrawPrimitive.

Most common options are:

| Option                        |
|-------------------------------|
| ZEN::DrawPrimitive::Points    |
| ZEN::DrawPrimitive::Lines     |
| ZEN::DrawPrimitive::Triangles |
