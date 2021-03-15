#include "scene.hpp"

#include <catch2/catch.hpp>

TEST_CASE("[FirstScene] - trace")
{
    constexpr Camera camera{Pointf{0.0f, 0.0f, 500.0f},
                            Vectorf{0.0f},
                            Vectorf{0.0f, 1.0f, 0.0f},
                            500.0f};

    constexpr FirstScene scene{camera};
    constexpr auto dir    = scene.get_camera().get_ray_direction(Pointf{0.0f});
    constexpr auto result = scene.trace(Rayf{Pointf{0.0f}, dir});

    REQUIRE(result.b() == 1.0f);
}