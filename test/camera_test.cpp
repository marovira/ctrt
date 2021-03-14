#include "camera.hpp"

#include <catch2/catch.hpp>

TEST_CASE("[Camera] - get_ray")
{
    constexpr Camera<100, 100> camera;
    constexpr auto result = camera.get_ray(0, 0);

    REQUIRE(result.origin == Vectorf{0.0f});
    REQUIRE(result.direction == Vectorf{-1.0f});
}
