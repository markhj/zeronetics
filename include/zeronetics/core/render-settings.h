#pragma once

namespace ZEN {
    struct RenderSettings {
        bool depthTesting = true;

        DrawPrimitive draw = DrawPrimitive::Triangles;
    };
}
