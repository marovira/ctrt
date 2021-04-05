#pragma once

#include "ray.hpp"

class Renderer
{
public:
    template<class Image, class Scene>
    static constexpr void render(Image& image, Scene const& scene)
    {
        Ray ray{Point{0.0f, 0.0f, 500.0f}, Vector{0.0f}};

        const float width  = static_cast<float>(Image::width);
        const float height = static_cast<float>(Image::height);

        auto const& lights    = scene.get_lights();
        auto const& materials = scene.get_materials();
        auto const& shapes    = scene.get_shapes();

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

                Colour colour{0.0f};
                bool bHit{false};
                for (auto const& shape : scene.get_shapes())
                {
                    if (auto result = shape.hit(ray); result)
                    {
                        auto rec        = *result;
                        int material_id = rec.material_id;
                        colour =
                            materials[material_id].shade(rec, lights, shapes);
                        bHit = true;
                        break;
                    }
                }

                if (!bHit)
                {
                    colour = scene.get_background_colour(ray);
                }

                image(row, col) = colour;
            }
        }
    }
};
