@page grid-3d 3D Grid

The **3D Grid** is mainly used in editors, but can just as easily be used in
game worlds, if somehow relevant.

![](https://res.cloudinary.com/drfztvfdh/image/upload/v1724513027/zeronetics/3d-grid_cfspww.png)

A 3D grid consists of _X_ number of lines, and at the center it has
lines indicating the positive directions of the X, Y and Z axes.

X-axis is red, Y-axis is green and Z-axis is blue.
This can also be remembered by the axis letters corresponding to Red-Green-Blue
(``XYZ = RGB``), in that ``X = R``, ``Y = G`` and ``Z = B``.

## 🎲 How it works

The class which generates the 3D grid has a method named ``generate``, which
creates a @ref ZEN::RenderLayer "render layer", which can be added to a
@ref render-manager "render manager".

Furthermore, it provides a @ref ZEN::ShaderBlueprint "shader blueprint", which
must be compiled by the used renderer.

## 🔨 Working with 3D grid

### Setting up

First of all, we must generate an instance of the ``ZEN::Gizmos::Grid3D`` class.

````cpp
auto grid3d = ZEN::Gizmos::Grid3D();

// Add configuration here, for example:
grid3d.lines = 30;
````

As shown above, you should add whatever configuration you'd like here,
because once the grid has been generated, changing the configuration will
no longer have an effect.

Next, we generate the @ref ZEN::RenderLayer "render layer", and attach
it to the @ref ZEN::RenderManager "render manager".

````cpp
m_gridLayer = std::make_shared<RenderLayer>(grid3d.generate());

m_renderManager->attachLayer(m_gridLayer);
````

### Example: Compiling shader for OpenGL

To properly display the grid, you can (optionally) use the
@ref ZEN::ShaderBlueprint "shader blueprint" bundled with the 3D Grid.

In this example, we demonstrate how to do this for the
@ref opengl "common Zeronetics OpenGL renderer".

````cpp
ZEN::GLSLShaderBuilder shaderBuilder;
std::string gridVertex = shaderBuilder.make(grid3d.getShaderBlueprint(), ShaderStage::Vertex).value();
std::string gridFrag = shaderBuilder.make(grid3d.getShaderBlueprint(), ShaderStage::Fragment).value();
````

This sets up the shader builder, and now we compile:

````cpp
std::shared_ptr<ZEN::OpenGL::Shader> gridShader;
gridShader = std::make_shared<ZEN::OpenGL::Shader>(ZEN::OpenGL::Shader());
gridShader->create();
gridShader->setSource(ShaderStage::Vertex, gridVertex);
gridShader->setSource(ShaderStage::Fragment, gridFrag);
gridShader->compile();
````

### Final touches

Just before we wrap up, we need to attach the shader to the render layer,
as well as the camera.

````cpp
m_gridLayer->renderGroups3d[0]->shader = gridShader;
m_gridLayer->camera3d = your3DCamera;
````

Note that you must replace ``your3DCamera`` which the variable
name of the @ref ZEN::Camera3D "3D camera" you're using.

Last, but not least, the render manager must be requested to allocate
the vertices contained in the render layer.

````cpp
m_renderManager->request(RendererRequest{
        RenderManagerRequest::Allocate,
        m_gridLayer->renderGroups3d[0]->renderables3d["Lines"],
        m_gridLayer,
});
````

## 📌 See also

ZEN::Gizmos::Grid3D
