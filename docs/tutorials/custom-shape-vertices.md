@page custom-shape-vertices Custom shape from vertices

Creating a custom 3D shape from a set of vertices is quite easy.
In essence, you instantiate a ZEN::Shape3D with the set of vertices
as its constructor.

````cpp
std::vector<Vertex3D> vertices = { ... };

Shape3D myShape(vertices);
````

Now you can work with the shape, for example using it for ZEN::Mesh3D.

````cpp
Mesh3D myMesh(myShape);
````

## 📌 See also

@ref ZEN::Vertex3D  
@ref custom-shape-class
