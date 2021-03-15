#define CTRT_DEFINE_SAVE_IMAGE
#include "canvas.hpp"
#include "scene.hpp"

#include <fmt/printf.h>
#include <zeus/timer.hpp>

template<typename T, class Canvas>
constexpr void render(Scene<T> const& scene, Canvas& canvas)
{
    Rayf ray{Pointf{0.0f, 0.0f, 500.0f}, Vectorf{0.0f}};

    for (std::size_t row{0}; row < canvas.get_height(); ++row)
    {
        for (std::size_t col{0}; col < canvas.get_width(); ++col)
        {
            Pointf sample_pt{0.5f, 0.5f, 0.0f};
            Pointf pixel_pt{col - 0.5f * canvas.get_width() + sample_pt.x(),
                            row - 0.5f * canvas.get_height() + sample_pt.y(),
                            0.0f};
            ray.direction  = scene.get_camera().get_ray_direction(pixel_pt);
            Colourf colour = scene.trace(ray);

            canvas.set_pixel(row, col, colour);
        }
    }
}

int main()
{
    constexpr std::size_t image_width{512};
    constexpr std::size_t image_height{512};

#if defined(CTRT_DO_STATIC_RENDER)
    constexpr auto canvas = []() {
        StaticCanvas<image_width, image_height> canvas;
        constexpr Camera camera{Pointf{0.0f, 0.0f, 500.0f},
                                Vectorf{0.0f},
                                Vectorf{0.0f, 1.0f, 0.0f},
                                500.0f};
        constexpr FirstScene scene{camera};

        render(scene, canvas);
        return canvas;
    }();

#else
    RuntimeCanvas canvas{image_width, image_height};
    Camera camera{Pointf{0.0f, 0.0f, 500.0f},
                  Vectorf{0.0f},
                  Vectorf{0.0f, 1.0f, 0.0f},
                  500.0f};
    FirstScene scene{camera};

    zeus::Timer<float> timer;

    timer.start();
    render(scene, canvas);
    auto elapsed = timer.elapsed();
    fmt::print("render in: {} ms\n", elapsed * 100);
#endif

    save_image("../render.jpg", canvas);

    return 0;
}
