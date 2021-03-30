#include "scene.hpp"

#include <catch2/catch.hpp>

TEST_CASE("[FirstScene] - trace")
{
    constexpr Camera camera{Point{0.0f, 0.0f, 500.0f},
                            Vector{0.0f},
                            Vector{0.0f, 1.0f, 0.0f},
                            500.0f};

    FirstScene scene;
    scene.set_camera(camera);
    auto dir    = scene.get_camera().get_ray_direction(Point{0.0f});
    auto result = scene.trace_simple(Ray{Point{0.0f}, dir});

    REQUIRE(result.b() == 1.0f);
}
