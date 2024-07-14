@page tensors Tensors

The **tensors** in Zeronetics currently include:

- Vectors in 2D, 3D and 4D
- 4x4 Matrix

## ↗️ Vectors

There are three **vectors** are:

| Class         |
|---------------|
| ``ZEN::Vec2`` |
| ``ZEN::Vec3`` |
| ``ZEN::Vec4`` |

They can be initialized with all axes or with scalar. For instance:

````cpp
// By coordinate
Vec3 size(1.0, 2.0, 3.0);

// Scalar
Vec3 position(0.0);
````

## 🔢 Matrices

There's currently just the ``ZEN::Mat4x4`` matrix available.

## 🔧 Implementation

``Vec2``, ``Vec3``, ``Vec4`` and ``Mat4x4`` are based on
corresponding implementations in [GLM](https://github.com/g-truc/glm).
