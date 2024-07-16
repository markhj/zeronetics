@page shapes Shapes

As you can read in the
@ref geometry-relationships "article about geometric relationships"
it's cumbersome to build shapes by specifying all the vertices and
triangles they are made of. The concept of "shapes" is a way
to ease this process.

## 🔷 Shapes

Every child class of ZEN::Shape contains a 
@ref ZEN::IShape::getVertices "getVertices" method, which returns
the vertices that make up the shape.

Example:

````cpp
ZEN::Cube cube(1.0, 5.0, 2.5);  // Width, height, depth
````

## 📃 List of shapes

| Class | Description     |
| -- |-----------------|
| ZEN::Cube | Forms a 3D cube |

## ⭕ Custom shapes

You can build your own shapes by extended ZEN::Shape3D, and implementing
the ZEN::IShape::make method.

The normal process is defining a constructor which takes the properties
you need. A sphere, for instance, needs a radius.

@note Important: You must write your shape code such that the center
of the object is at ``(0, 0, 0)``, otherwise positioning will not
work as expected.

## 📜 See also

@ref geometry-relationships
