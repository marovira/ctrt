#include "vector.hpp"

#include <fmt/printf.h>
#include <stb_image_write.h>

template<std::size_t width, std::size_t height>
constexpr std::array<math::Vectorf, width * height> render()
{
    std::array<math::Vectorf, width * height> image;
    for (std::size_t row{0}; row < width; ++row)
    {
        for (std::size_t col{0}; col < height; ++col)
        {
            math::Colourf colour{static_cast<float>(col) / (height - 1),
                                 static_cast<float>(row) / (width - 1),
                                 0.25f};
            image[(row * width) + col] = colour;
        }
    }

    return image;
}

struct Image
{
    static constexpr std::size_t width{100};
    static constexpr std::size_t height{100};
    static constexpr std::size_t size{width * height};
    static constexpr std::array<math::Colourf, size> data =
        render<width, height>();
};

using Pixel = unsigned char;

int main()
{
    std::array<Pixel, Image::size * 3> pixel_buffer;

    std::size_t i{0};
    for (std::size_t row{0}; row < Image::width; ++row)
    {
        for (std::size_t col{0}; col < Image::height; ++col)
        {
            auto colour       = Image::data[(row * Image::width) + col];
            pixel_buffer[i++] = static_cast<Pixel>(255.0f * colour.r());
            pixel_buffer[i++] = static_cast<Pixel>(255.0f * colour.g());
            pixel_buffer[i++] = static_cast<Pixel>(255.0f * colour.b());
        }
    }

    stbi_write_jpg("render.jpg",
                   Image::width,
                   Image::height,
                   3,
                   pixel_buffer.data(),
                   Image::width * 3);

    return 0;
}
