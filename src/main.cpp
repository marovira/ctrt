#define CTRT_DEFINE_SAVE_IMAGE
#include "image.hpp"
#include "renderer.hpp"
#include "scene.hpp"

#include <fmt/printf.h>
#include <zeus/timer.hpp>

constexpr std::size_t image_width{512};
constexpr std::size_t image_height{512};

#define CTRT_RENDER_SCENE_3
//#define CTRT_DO_STATIC_RENDER

#if defined(CTRT_RENDER_SCENE_1)
auto render_scene_1()
{
#    if defined(CTRT_DO_STATIC_RENDER)
    constexpr auto image = []() {
        StaticImage<image_width, image_height> image;

        Camera camera{Point{0.0f, 0.0f, 500.0f},
                      Vector{0.0f},
                      Vector{0.0f, 1.0f, 0.0f},
                      500.0f};

        std::array<Shapes, 0> shapes{};
        std::array<Lights, 0> lights{};
        std::array<Materials, 0> materials{};

        Scene<decltype(shapes),
              decltype(lights),
              decltype(materials),
              GradientBackground>
            scene{std::move(shapes),
                  std::move(lights),
                  std::move(materials),
                  GradientBackground{}};
        scene.set_camera(camera);

        Renderer::render(image, scene);
        return image;
    }();

    return image;
#    else
    DynamicImage<image_width, image_height> image;
    Camera camera{Point{0.0f, 0.0f, 500.0f},
                  Vector{0.0f},
                  Vector{0.0f, 1.0f, 0.0f},
                  500.0f};

    std::array<Shapes, 0> shapes{};
    std::array<Lights, 0> lights{};
    std::array<Materials, 0> materials{};

    Scene<decltype(shapes),
          decltype(lights),
          decltype(materials),
          GradientBackground>
        scene{std::move(shapes),
              std::move(lights),
              std::move(materials),
              GradientBackground{}};
    scene.set_camera(camera);

    Renderer::render(image, scene);
    return image;
#    endif
}
#endif

#if defined(CTRT_RENDER_SCENE_2)
auto render_scene_2()
{
#    if defined(CTRT_DO_STATIC_RENDER)
    constexpr auto image = []() {
        StaticImage<image_width, image_height> image;
        Camera camera{Point{0.0f, 0.0f, 500.0f},
                      Vector{0.0f},
                      Vector{0.0f, 1.0f, 0.0f},
                      500.0f};

        Sphere s{Point{0.0f}, 150.0f};
        s.set_default_colour(Colour{1.0f, 0.0f, 0.0f});
        s.set_material_id(0);

        std::array<Shapes, 1> shapes{s};
        std::array<Lights, 1> lights{AmbientLight{}};
        std::array<Materials, 1> materials{EmptyMaterial{}};

        Scene<decltype(shapes),
              decltype(lights),
              decltype(materials),
              GradientBackground>
            scene{shapes, lights, materials, GradientBackground{}};
        scene.set_camera(camera);

        Renderer::render(image, scene);
        return image;
    }();

    return image;

#    else
    DynamicImage<image_width, image_height> image;
    Camera camera{Point{0.0f, 0.0f, 500.0f},
                  Vector{0.0f},
                  Vector{0.0f, 1.0f, 0.0f},
                  500.0f};

    Sphere s{Point{0.0f}, 150.0f};
    s.set_default_colour(Colour{1.0f, 0.0f, 0.0f});
    s.set_material_id(0);

    std::array<Shapes, 1> shapes{s};
    std::array<Lights, 1> lights{AmbientLight{}};
    std::array<Materials, 1> materials{EmptyMaterial{}};

    Scene<decltype(shapes),
          decltype(lights),
          decltype(materials),
          DefaultBackground>
        scene{shapes, lights, materials, DefaultBackground{}};
    scene.set_camera(camera);

    Renderer::render(image, scene);
    return image;
#    endif
}
#endif

#if defined(CTRT_RENDER_SCENE_3)
auto render_scene_3()
{
#    if defined(CTRT_DO_STATIC_RENDER)
    constexpr auto image = []() {
        StaticImage<image_width, image_height> image;
        Camera camera{Point{0.0f, 0.0f, 500.0f},
                      Vector{0.0f, 0.0f, 0.0f},
                      Vector{0.0f, 1.0f, 0.0f},
                      950.0f};

        AmbientLight ambient;
        ambient.set_radiance(1.0f);

        PointLight light;
        light.set_position(Point{100.0f, 60.0f, 50.0f});
        light.set_radiance(3.0f);
        light.set_casts_shadows(true);

        Matte yellow_matte;
        yellow_matte.set_ambient_reflection(0.25f);
        yellow_matte.set_diffuse_reflection(0.65f);
        yellow_matte.set_diffuse_colour(Colour{1.0f, 1.0f, 0.0f});

        Matte brown_matte;
        brown_matte.set_ambient_reflection(0.15f);
        brown_matte.set_diffuse_reflection(0.85f);
        brown_matte.set_diffuse_colour(Colour{0.71f, 0.4f, 0.16f});

        Matte green_matte;
        green_matte.set_ambient_reflection(0.15f);
        green_matte.set_diffuse_reflection(0.5f);
        green_matte.set_diffuse_colour(Colour{0.0f, 0.4f, 0.2f});

        Sphere yellow_sphere{Point{13.0f, -6.0f, 0.0f}, 35.0f};
        yellow_sphere.set_material_id(0);
        yellow_sphere.set_default_colour(Colour{1.0f, 1.0f, 0.0f});

        Sphere brown_sphere{Point{-32.0f, 13.0f, -45.0f}, 35.0f};
        brown_sphere.set_material_id(1);
        brown_sphere.set_default_colour(Colour{0.71f, 0.4f, 0.16f});

        Plane green_plane{Point{0.0f, 0.0f, -50.0f}, Vector{0.0f, 0.0f, 1.0f}};
        green_plane.set_material_id(2);
        green_plane.set_default_colour(Colour{0.0f, 0.4f, 0.2f});

        // Construct arrays.
        std::array<Lights, 2> lights{ambient, light};
        std::array<Matte, 3> materials{yellow_matte, brown_matte, green_matte};
        std::array<Shapes, 3> shapes{yellow_sphere, brown_sphere, green_plane};

        Scene<decltype(shapes),
              decltype(lights),
              decltype(materials),
              DefaultBackground>
            scene{std::move(shapes),
                  std::move(lights),
                  std::move(materials),
                  DefaultBackground{}};
        scene.set_camera(camera);

        Renderer::render(image, scene);
        return image;
    }();

    return image;
#    else
    DynamicImage<image_width, image_height> image;
    Camera camera{Point{0.0f, 0.0f, 500.0f},
                  Vector{0.0f, 0.0f, 0.0f},
                  Vector{0.0f, 1.0f, 0.0f},
                  950.0f};

    AmbientLight ambient;
    ambient.set_radiance(1.0f);

    PointLight light;
    light.set_position(Point{100.0f, 60.0f, 50.0f});
    light.set_radiance(3.0f);
    light.set_casts_shadows(true);

    Matte yellow_matte;
    yellow_matte.set_ambient_reflection(0.25f);
    yellow_matte.set_diffuse_reflection(0.65f);
    yellow_matte.set_diffuse_colour(Colour{1.0f, 1.0f, 0.0f});

    Matte brown_matte;
    brown_matte.set_ambient_reflection(0.15f);
    brown_matte.set_diffuse_reflection(0.85f);
    brown_matte.set_diffuse_colour(Colour{0.71f, 0.4f, 0.16f});

    Matte green_matte;
    green_matte.set_ambient_reflection(0.15f);
    green_matte.set_diffuse_reflection(0.5f);
    green_matte.set_diffuse_colour(Colour{0.0f, 0.4f, 0.2f});

    Sphere yellow_sphere{Point{13.0f, -6.0f, 0.0f}, 35.0f};
    yellow_sphere.set_material_id(0);
    yellow_sphere.set_default_colour(Colour{1.0f, 1.0f, 0.0f});

    Sphere brown_sphere{Point{-32.0f, 13.0f, -45.0f}, 35.0f};
    brown_sphere.set_material_id(1);
    brown_sphere.set_default_colour(Colour{0.71f, 0.4f, 0.16f});

    Plane green_plane{Point{0.0f, 0.0f, -50.0f}, Vector{0.0f, 0.0f, 1.0f}};
    green_plane.set_material_id(2);
    green_plane.set_default_colour(Colour{0.0f, 0.4f, 0.2f});

    // Construct arrays.
    std::array<Lights, 2> lights{ambient, light};
    std::array<Matte, 3> materials{yellow_matte, brown_matte, green_matte};
    std::array<Shapes, 3> shapes{yellow_sphere, brown_sphere, green_plane};

    Scene<decltype(shapes),
          decltype(lights),
          decltype(materials),
          DefaultBackground>
        scene{std::move(shapes),
              std::move(lights),
              std::move(materials),
              DefaultBackground{}};
    scene.set_camera(camera);

    Renderer::render(image, scene);
    return image;
#    endif
}
#endif

int main()
{
    fmt::print("\nStarting render...\n");
    zeus::Timer<double> timer;
    timer.start();
#if defined(CTRT_RENDER_SCENE_1)
    auto image = render_scene_1();
#elif defined(CTRT_RENDER_SCENE_2)
    auto image = render_scene_2();
#elif defined(CTRT_RENDER_SCENE_3)
    auto image = render_scene_3();
#endif
    fmt::print("Render finished in: {:.2f}ms\n", timer.elapsed());
    save_image("../render_test.jpg", image);

    return 0;
}
