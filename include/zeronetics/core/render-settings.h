#pragma once

namespace ZEN {
    struct RenderSettings {
        bool depthTesting = true;

        gw_float lineSize = 1.0;

        DrawPrimitive draw = DrawPrimitive::Triangles;
    };
}
