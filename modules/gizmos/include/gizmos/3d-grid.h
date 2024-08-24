#pragma once

#include "zeronetics/core/shader-blueprint.h"
#include "zeronetics/render/render-manager.h"

namespace ZEN::Gizmos {
    /**
     * Renders a grid in 3D with a plane on the horizontal (X, Z) axis,
     * as well as colored axis lines.
     *
     * X: Red (R)
     * Y: Green (G)
     * Z: Blue (B)
     *
     * @ref grid-3d
     */
    class Grid3D {
    public:
        /**
         * The number of lines on the horizontal grid
         */
        uint16_t lines = 10;

        /**
         * The spacing between each line.
         */
        gw_float spacing = 1.0;

        /**
         * Color of the grid lines.
         */
        ColorRGB lineColor = ColorRGB(1.0, 1.0, 1.0);

        /**
         * Color of the X-axis line at the center.
         */
        ColorRGB xAxisColor = ColorRGB(1.0, 0.0, 0.0);

        /**
         * Color of the Y-axis line at the center.
         */
        ColorRGB yAxisColor = ColorRGB(0.0, 1.0, 0.0);

        /**
         * Color of the Z-axis line at the center.
         */
        ColorRGB zAxisColor = ColorRGB(0.0, 0.0, 1.0);

        /**
         * Retrieve the blueprint for the shader which is suitable to
         * render the grid lines.
         *
         * @return
         */
        [[nodiscard]] ShaderBlueprint getShaderBlueprint() const noexcept;

        /**
         * Generate the ZEN::RenderLayer with the lines according to the
         * configuration above.
         *
         * @return
         */
        RenderLayer generate();

    private:
        std::vector<VertexAttribute> m_attributes = {
                VertexAttribute::Position3D,
                VertexAttribute::ColorRGB,
        };
    };
}
