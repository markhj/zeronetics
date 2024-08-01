#pragma once

namespace ZEN {
    /**
     * Container for fundamental image data
     */
    struct ImageData {
        /**
         * Image data
         */
        unsigned char* data;

        unsigned int width, height, channels;
    };
}
