#define CTRT_DEFINE_SAVE_IMAGE
#include "image.hpp"
#include "renderer.hpp"

#include <fmt/printf.h>
#include <zeus/timer.hpp>

constexpr std::size_t image_width{512};
constexpr std::size_t image_height{512};

//#define CTRT_DO_STATIC_RENDER

auto render_scene_1()
{
#if defined(CTRT_DO_STATIC_RENDER)
    constexpr auto image = []() {
        StaticImage<image_width, image_height> image;

        Camera camera{Point{0.0f, 0.0f, 500.0f},
                      Vector{0.0f},
                      Vector{0.0f, 1.0f, 0.0f},
                      500.0f};

        std::array<Shapes, 1> shapes{EmptyShape{}};

        Scene<decltype(shapes), GradientBackground> scene{shapes,
                                                          GradientBackground{}};
        scene.set_camera(camera);

        Renderer::render(image, scene);
        return image;
    }();

    return image;
#else
    DynamicImage<image_width, image_height> image;
    Camera camera{Point{0.0f, 0.0f, 500.0f},
                  Vector{0.0f},
                  Vector{0.0f, 1.0f, 0.0f},
                  500.0f};

    std::array<Shapes, 1> shapes{EmptyShape{}};

    Scene<decltype(shapes), GradientBackground> scene{shapes,
                                                      GradientBackground{}};
    scene.set_camera(camera);

    Renderer::render(image, scene);
    return image;
#endif
}

auto render_scene_2()
{
#if defined(CTRT_DO_STATIC_RENDER)
    constexpr auto image = []() {
        StaticImage<image_width, image_height> image;
        Camera camera{Point{0.0f, 0.0f, 500.0f},
                      Vector{0.0f},
                      Vector{0.0f, 1.0f, 0.0f},
                      500.0f};

        Sphere s{Point{0.0f}, 150.0f};
        s.set_default_colour(Colour{1.0f, 0.0f, 0.0f});

        std::array<Shapes, 1> shapes{s};

        Scene<decltype(shapes), DefaultBackground> scene{shapes,
                                                         DefaultBackground{}};
        scene.set_camera(camera);

        Renderer::render(image, scene);
        return image;
    }();

    return image;

#else
    DynamicImage<image_width, image_height> image;
    Camera camera{Point{0.0f, 0.0f, 500.0f},
                  Vector{0.0f},
                  Vector{0.0f, 1.0f, 0.0f},
                  500.0f};

    Sphere s{Point{0.0f}, 150.0f};
    s.set_default_colour(Colour{1.0f, 0.0f, 0.0f});

    std::array<Shapes, 1> shapes{s};

    Scene<decltype(shapes), DefaultBackground> scene{shapes,
                                                     DefaultBackground{}};
    scene.set_camera(camera);

    Renderer::render(image, scene);
    return image;
#endif
}

int main()
{
    auto image = render_scene_2();
    save_image("../render_test.jpg", image);

    return 0;
}
