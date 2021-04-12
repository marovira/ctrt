#pragma once

#include "ray.hpp"

struct Tile
{
    std::size_t x_start{0}, x_end{0};
    std::size_t y_start{0}, y_end{0};
    std::size_t width{0}, height{0};
};

class Renderer
{
public:
    template<class Image, class Scene>
    static constexpr void
    render(Image& image, Scene const& scene, Tile const& tile)
    {
        Ray ray;
        ray.origin = scene.get_camera().get_eye();

        const float width  = static_cast<float>(Image::width);
        const float height = static_cast<float>(Image::height);

        auto const& lights    = scene.get_lights();
        auto const& materials = scene.get_materials();
        auto const& shapes    = scene.get_shapes();

        for (std::size_t r{0}; r < tile.height; ++r)
        {
            for (std::size_t c{0}; c < tile.width; ++c)
            {
                std::size_t row = tile.y_start + r;
                std::size_t col = tile.x_start + c;

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
                        colour          = materials[material_id].shade(
                            rec, lights, shapes, materials);
                        bHit = true;
                        break;
                    }
                }

                if (!bHit)
                {
                    colour = scene.get_background_colour(ray);
                }

                image(r, c) = colour;
            }
        }
    }
};
