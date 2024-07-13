#include "zeronetics/entities/3d/mesh-3d.h"

std::vector<ZEN::Vertex3D> ZEN::Mesh3D::getVertices() const noexcept {
    return {
            Vertex3D{Vec3(0.0, 0.0, 0.0) + position, ColorRGB(1.0, 1.0, 0.0)},
            Vertex3D{Vec3(1.0, 0.0, 0.0) + position, ColorRGB(1.0, 1.0, 1.0)},
            Vertex3D{Vec3(0.0, 1.0, 0.0) + position, ColorRGB(0.0, 0.0, 1.0)},
    };
}
