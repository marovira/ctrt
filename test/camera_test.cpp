#include "camera.hpp"

#include <catch2/catch.hpp>

TEST_CASE("[Camera] - get_ray")
{
    constexpr Camera camera{Point{0.0f, 0.0f, 500.0f},
                            Vector{0.0f},
                            Vector{0.0f, 1.0f, 0.0f},
                            500.0f};
    auto result = camera.get_ray_direction(Point{0.0f});

    REQUIRE(result == Vector{0.0f, 0.0f, -1.0f});
}
