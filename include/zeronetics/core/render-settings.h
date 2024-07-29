#pragma once

namespace ZEN {
    /**
     * Settings on a per-layer basis.
     * Every layer is coupled with an instance of this struct,
     * which allows every layer to have individual preferences
     * such as depth testing and draw mode.
     */
    struct RenderSettings {
        /**
         * Enable or disable depth testing
         *
         * When depth resting is enabled it's the Z-coordinate of a vertex
         * which determines the visible order. When it's disabled, it's the
         * order in which vertices are rendered which take priority.
         */
        bool depthTesting = true;

        /**
         * The width of line primitives.
         */
        gw_float lineSize = 1.0;

        /**
         * The draw mode. Among a few options are points, lines and triangles.
         * Triangles are the common choice to rendering 3D objects.
         */
        DrawPrimitive draw = DrawPrimitive::Triangles;
    };
}
