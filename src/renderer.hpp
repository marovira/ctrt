#pragma once

#include "scene.hpp"

class Renderer
{
public:
    template<typename T, class Image>
    static constexpr void render_simple(Scene<T> const& scene, Image& image)
    {
        Rayf ray{Pointf{0.0f, 0.0f, 500.0f}, Vectorf{0.0f}};

        const float width  = static_cast<float>(Image::width);
        const float height = static_cast<float>(Image::height);

        for (std::size_t row{0}; row < Image::height; ++row)
        {
            for (std::size_t col{0}; col < Image::width; ++col)
            {
                Pointf sample_pt{0.5f, 0.5f, 0.0f};
                Pointf pixel_pt{
                    static_cast<float>(col) - 0.5f * width + sample_pt.x(),
                    static_cast<float>(row) - 0.5f * height + sample_pt.y(),
                    0.0f};
                ray.direction  = scene.get_camera().get_ray_direction(pixel_pt);
                Colourf colour = scene.trace_simple(ray);

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
        Rayf ray{Pointf{0.0f, 0.0f, 500.0f}, Vectorf{0.0f}};

        const float width  = static_cast<float>(Image::width);
        const float height = static_cast<float>(Image::height);

        for (std::size_t row{0}; row < Image::height; ++row)
        {
            for (std::size_t col{0}; col < Image::width; ++col)
            {
                Pointf sample_pt{0.5f, 0.5f, 0.0f};
                Pointf pixel_pt{
                    static_cast<float>(col) - 0.5f * width + sample_pt.x(),
                    static_cast<float>(row) - 0.5f * height + sample_pt.y(),
                    0.0f};
                ray.direction  = scene.get_camera().get_ray_direction(pixel_pt);
                Colourf colour = scene.trace(ray, shapes, materials);

                image(row, col) = colour;
            }
        }
    }
};
