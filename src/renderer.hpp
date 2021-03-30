#pragma once

#include "scene.hpp"

class Renderer
{
public:
    template<typename T, class Image>
    static constexpr void render_simple(Scene<T> const& scene, Image& image)
    {
        Ray ray{Point{0.0f, 0.0f, 500.0f}, Vector{0.0f}};

        const float width  = static_cast<float>(Image::width);
        const float height = static_cast<float>(Image::height);

        for (std::size_t row{0}; row < Image::height; ++row)
        {
            for (std::size_t col{0}; col < Image::width; ++col)
            {
                Point sample_pt{0.5f, 0.5f, 0.0f};
                Point pixel_pt{
                    static_cast<float>(col) - 0.5f * width + sample_pt.x(),
                    static_cast<float>(row) - 0.5f * height + sample_pt.y(),
                    0.0f};
                ray.direction = scene.get_camera().get_ray_direction(pixel_pt);
                Colour colour = scene.trace_simple(ray);

                image(row, col) = colour;
            }
        }
    }

    template<typename T,
             class Image,
             class ShapeContainer,
             class MaterialContainer>
    static constexpr void render(Scene<T> const& scene,
                                 Image& image,
                                 ShapeContainer const& shapes,
                                 MaterialContainer const& materials)
    {
        Ray ray{Point{0.0f, 0.0f, 500.0f}, Vector{0.0f}};

        const float width  = static_cast<float>(Image::width);
        const float height = static_cast<float>(Image::height);

        for (std::size_t row{0}; row < Image::height; ++row)
        {
            for (std::size_t col{0}; col < Image::width; ++col)
            {
                Point sample_pt{0.5f, 0.5f, 0.0f};
                Point pixel_pt{
                    static_cast<float>(col) - 0.5f * width + sample_pt.x(),
                    static_cast<float>(row) - 0.5f * height + sample_pt.y(),
                    0.0f};
                ray.direction = scene.get_camera().get_ray_direction(pixel_pt);
                image(row, col) = scene.trace(ray, shapes, materials);
            }
        }
    }
};
