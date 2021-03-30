#pragma once

#include "vector.hpp"

#include <string>
#include <vector>
#include <zeus/assert.hpp>

enum class ImageType
{
    static_image,
    dynamic_image
};

template<class Container,
         std::size_t image_width,
         std::size_t image_height,
         ImageType type>
class Image
{
public:
    static constexpr std::size_t width{image_width};
    static constexpr std::size_t height{image_height};
    static constexpr std::size_t size{width * height};
    static constexpr int channels{3};

    constexpr Image()
    {
        if constexpr (type == ImageType::dynamic_image)
        {
            m_data.resize(width * height);
        }
    }

    constexpr auto& operator()(std::size_t row, std::size_t col)
    {
        return m_data[(row * width) + col];
    }

    constexpr auto operator()(std::size_t row, std::size_t col) const
    {
        return m_data[(row * width) + col];
    }

    constexpr Container get_data() const
    {
        return m_data;
    }

private:
    Container m_data;
};

template<std::size_t width, std::size_t height>
using StaticImage = Image<std::array<Colour, width * height>,
                          width,
                          height,
                          ImageType::static_image>;

template<std::size_t width, std::size_t height>
using DynamicImage =
    Image<std::vector<Colour>, width, height, ImageType::dynamic_image>;

#if defined(CTRT_DEFINE_SAVE_IMAGE)
#    include <stb_image_write.h>

template<class Image>
void save_image(std::string const& filename, Image const& image)
{
    using Pixel = unsigned char;

    // First convert the image to pixels.
    std::vector<Pixel> pixel_buffer;
    pixel_buffer.resize(Image::size * Image::channels);
    std::size_t i{0};
    for (std::size_t row{0}; row < Image::width; ++row)
    {
        for (std::size_t col{0}; col < Image::height; ++col)
        {
            Colour colour     = image(row, col);
            pixel_buffer[i++] = static_cast<Pixel>(255.0f * colour.r());
            pixel_buffer[i++] = static_cast<Pixel>(255.0f * colour.g());
            pixel_buffer[i++] = static_cast<Pixel>(255.0f * colour.b());
        }
    }

    stbi_write_jpg(filename.c_str(),
                   static_cast<int>(Image::width),
                   static_cast<int>(Image::height),
                   Image::channels,
                   pixel_buffer.data(),
                   static_cast<int>(Image::channels * Image::width));
}
#endif
