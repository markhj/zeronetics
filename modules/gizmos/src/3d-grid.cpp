#include "gizmos/3d-grid.h"
#include "zeronetics/entities/3d/mesh-3d.h"
#include "zeronetics/shapes/3d/cube.h"

ZEN::RenderLayer ZEN::Gizmos::Grid3D::generate() {
    RenderLayer renderLayer(m_attributes);
    renderLayer.settings.draw = DrawPrimitive::Lines;
    renderLayer.settings.lineSize = 2.0;

    Vec3 normal(0.0);

    std::vector<Vertex3D> vertices;
    gw_float lineLength = static_cast<gw_float>(lines) * spacing;
    gw_float halfLine = lineLength / 2.0f;
    gw_float d = -halfLine;

    // Draw lines that stop shortly before the center
    for (const gw_float posNeg: {1.0f, -1.0f}) {
        vertices.push_back({.position = Vec3(posNeg * halfLine, 0.0, 0.0), .normal = normal});
        vertices.push_back({.position = Vec3(posNeg * spacing, 0.0, 0.0), .normal = normal});
        vertices.push_back({.position = Vec3(0.0, 0.0, posNeg * halfLine), .normal = normal});
        vertices.push_back({.position = Vec3(0.0, 0.0, posNeg * spacing), .normal = normal});
    }

    // Draw axis lines
    gw_float axisLength = spacing * 0.9f;
    vertices.push_back({.position = Vec3(), .color = xAxisColor, .normal = normal});
    vertices.push_back({.position = Vec3(axisLength, 0.0, 0.0), .color = xAxisColor, .normal = normal});
    vertices.push_back({.position = Vec3(), .color = yAxisColor, .normal = normal});
    vertices.push_back({.position = Vec3(0.0, axisLength, 0.0), .color = yAxisColor, .normal = normal});
    vertices.push_back({.position = Vec3(), .color = zAxisColor, .normal = normal});
    vertices.push_back({.position = Vec3(0.0, 0.0, axisLength), .color = zAxisColor, .normal = normal});

    // Draw other lines
    for (uint16_t i = 1; i <= lines / 2; ++i) {
        for (const gw_float posNeg: {1.0f, -1.0f}) {
            vertices.push_back({.position = Vec3(posNeg * d, 0.0, -halfLine), .color = lineColor, .normal = normal});
            vertices.push_back({.position = Vec3(posNeg * d, 0.0, halfLine), .color = lineColor, .normal = normal});
            vertices.push_back({.position = Vec3(-halfLine, 0.0, posNeg * d), .color = lineColor, .normal = normal});
            vertices.push_back({.position = Vec3(halfLine, 0.0, posNeg * d), .color = lineColor, .normal = normal});
        }
        d += spacing;
    }

    std::shared_ptr<Shape3D> gridShape = std::make_shared<Shape3D>(Shape3D(vertices));

    std::shared_ptr<RenderGroup3D> group = std::make_shared<RenderGroup3D>(RenderGroup3D());
    group->renderables3d["Lines"] = std::make_shared<Mesh3D>(Mesh3D(gridShape));
    renderLayer.renderGroups3d.push_back(group);

    return renderLayer;
}

ZEN::ShaderBlueprint ZEN::Gizmos::Grid3D::getShaderBlueprint() const noexcept {
    return {
            .attributes = m_attributes,
            .projection = Projection::Perspective,
    };
}
