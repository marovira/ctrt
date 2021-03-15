#define CTRT_DEFINE_SAVE_IMAGE
#include "image.hpp"
#include "scene.hpp"

#include <fmt/printf.h>
#include <zeus/timer.hpp>

template<typename T, class Image>
constexpr void render(Scene<T> const& scene, Image& image)
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
            Colourf colour = scene.trace(ray);

            image(row, col) = colour;
        }
    }
}

constexpr std::size_t image_width{50};
constexpr std::size_t image_height{50};

//#define CTRT_DO_STATIC_RENDER
int main()
{
#if defined(CTRT_DO_STATIC_RENDER)
    constexpr auto image = []() {
        StaticImage<image_width, image_height> image;
        Camera camera{Pointf{0.0f, 0.0f, 500.0f},
                      Vectorf{0.0f},
                      Vectorf{0.0f, 1.0f, 0.0f},
                      500.0f};

        FirstScene scene;
        scene.set_camera(camera);

        render(scene, image);
        return image;
    }();

#else
    DynamicImage<image_width, image_height> image;
    Camera camera{Pointf{0.0f, 0.0f, 500.0f},
                  Vectorf{0.0f},
                  Vectorf{0.0f, 1.0f, 0.0f},
                  500.0f};
    FirstScene scene;
    scene.set_camera(camera);

    zeus::Timer<float> timer;

    timer.start();
    render(scene, image);
    auto elapsed = timer.elapsed();
    fmt::print("render in: {} ms\n", elapsed * 100);
#endif

    save_image("../render_test.jpg", image);

    return 0;
}
