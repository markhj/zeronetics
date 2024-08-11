@page tensors Tensors

The **tensors** in Zeronetics currently include:

- Vectors in 2, 3 and 4 dimensions
- 4x4 Matrix

These classes are implemented as extensions of
[GLM](https://github.com/g-truc/glm).

## ↗️ Classes

| Class           |
|-----------------|
| ``ZEN::Vec2``   |
| ``ZEN::Vec3``   |
| ``ZEN::Vec4``   |
| ``ZEN::Mat4x4`` |

## 🔢 Initialization

They can be initialized with all axes or with scalar. For instance:

````cpp
// By coordinate
Vec3 size(1.0, 2.0, 3.0);

// Scalar
Vec3 position(0.0);
````

## ➕ Arithmetic operations

You can add and subtract using:

````cpp
Vec3 a(1.0), b(2.0);

Vec3 added = a + b;
Vec3 sub = a - b;
````

You can also multiply and divide the components:

````cpp
Vec3 a(1.0);

Vec3 b = a * 3.0;
Vec3 c = a / 1.5;
````
