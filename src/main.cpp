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

        FirstScene scene;
        scene.set_camera(camera);

        Renderer::render_simple(scene, image);
        return image;
    }();

    return image;
#else
    DynamicImage<image_width, image_height> image;
    Camera camera{Point{0.0f, 0.0f, 500.0f},
                  Vector{0.0f},
                  Vector{0.0f, 1.0f, 0.0f},
                  500.0f};
    FirstScene scene;
    scene.set_camera(camera);

    zeus::Timer<float> timer;

    timer.start();
    Renderer::render_simple(scene, image);
    auto elapsed = timer.elapsed();
    fmt::print("render in: {} ms\n", elapsed * 100);
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

        std::array<Shapes, 1> shapes_list{Sphere{Point{0.0f}, 150.0f}};
        std::array<Materials, 1> materials_list{DefaultMaterial{}};
        ShapeContainer<decltype(shapes_list)> shapes{std::move(shapes_list)};
        MaterialContainer<decltype(materials_list)> materials{
            std::move(materials_list)};

        SphereScene scene;
        scene.set_camera(camera);

        Renderer::render(scene, image, shapes, materials);
        return image;
    }();

    return image;
#else
    DynamicImage<image_width, image_height> image;
    Camera camera{Point{0.0f, 0.0f, 500.0f},
                  Vector{0.0f},
                  Vector{0.0f, 1.0f, 0.0f},
                  500.0f};

    std::array<Shapes, 1> shapes_list{Sphere{Point{0.0f}, 150.0f}};
    std::array<Materials, 1> materials_list{DefaultMaterial{}};
    ShapeContainer<decltype(shapes_list)> shapes{std::move(shapes_list)};
    MaterialContainer<decltype(materials_list)> materials{
        std::move(materials_list)};

    SphereScene scene;
    scene.set_camera(camera);

    zeus::Timer<float> timer;
    timer.start();
    Renderer::render(scene, image, shapes, materials);
    auto elapsed = timer.elapsed();
    fmt::print("render in: {} ms\n", elapsed * 100);
    return image;
#endif
}

int main()
{
    auto image = render_scene_2();
    save_image("../render_test.jpg", image);

    return 0;
}
