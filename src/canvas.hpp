#pragma once

#include "vector.hpp"

#include <string>
#include <vector>
#include <zeus/assert.hpp>

template<std::size_t width, std::size_t height>
class StaticCanvas
{
public:
    constexpr void
    set_pixel(std::size_t row, std::size_t col, Colourf const& colour)
    {
        m_image[(row * width) + col] = colour;
    }

    constexpr std::array<Colourf, width * height> get_image() const
    {
        return m_image;
    }

    constexpr std::size_t get_width() const
    {
        return width;
    }

    constexpr std::size_t get_height() const
    {
        return height;
    }

    static constexpr int channels{3};

private:
    std::array<Colourf, width * height> m_image;
};

class RuntimeCanvas
{
public:
    RuntimeCanvas(std::size_t width, std::size_t height) :
        m_width{width}, m_height{height}
    {
        m_image.resize(width * height);
    }

    void set_pixel(std::size_t row, std::size_t col, Colourf const& colour)
    {
        ASSERT(row < m_width);
        ASSERT(row < m_height);
        ASSERT(!std::isnan(colour.r()));
        ASSERT(!std::isnan(colour.g()));
        ASSERT(!std::isnan(colour.b()));

        m_image[(row * m_width) + col] = colour;
    }

    std::vector<Colourf> get_image() const
    {
        return m_image;
    }

    std::size_t get_width() const
    {
        return m_width;
    }

    std::size_t get_height() const
    {
        return m_height;
    }

    static constexpr int channels{3};

private:
    std::size_t m_width;
    std::size_t m_height;
    std::vector<Colourf> m_image;
};

#if defined(CTRT_DEFINE_SAVE_IMAGE)
#    include <stb_image_write.h>

template<class Canvas>
void save_image(std::string const& filename, Canvas const& canvas)
{
    using Pixel = unsigned char;

    auto image = canvas.get_image();

    // First convert the image to pixels.
    std::vector<Pixel> pixel_buffer;
    pixel_buffer.resize(image.size() * Canvas::channels);
    std::size_t i{0};
    for (std::size_t row{0}; row < canvas.get_width(); ++row)
    {
        for (std::size_t col{0}; col < canvas.get_height(); ++col)
        {
            Colourf colour    = image[(row * canvas.get_width()) + col];
            pixel_buffer[i++] = static_cast<Pixel>(255.0f * colour.r());
            pixel_buffer[i++] = static_cast<Pixel>(255.0f * colour.g());
            pixel_buffer[i++] = static_cast<Pixel>(255.0f * colour.b());
        }
    }

    stbi_write_jpg(filename.c_str(),
                   static_cast<int>(canvas.get_width()),
                   static_cast<int>(canvas.get_height()),
                   Canvas::channels,
                   pixel_buffer.data(),
                   static_cast<int>(Canvas::channels * canvas.get_width()));
}
#endif
