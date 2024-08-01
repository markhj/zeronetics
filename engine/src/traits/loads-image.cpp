#include "zeronetics/traits/loads-images.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

std::optional<ZEN::ImageData> ZEN::Traits::LoadsImages::loadImage(const Path &path) {
    int width, height, nrChannels;
    auto p = path.getAbsolute();
    const char *filename = p.c_str();

    unsigned char *data = stbi_load(filename,
                                    &width,
                                    &height,
                                    &nrChannels,
                                    0);

    if (!data) {
        return std::nullopt;
    }

    return ImageData{
            .data = data,
            .width = static_cast<unsigned int>(width),
            .height = static_cast<unsigned int>(height),
            .channels = static_cast<unsigned int>(nrChannels)};
}
