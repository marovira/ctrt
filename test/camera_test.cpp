#include "camera.hpp"

#include <catch2/catch.hpp>

TEST_CASE("[Camera] - get_ray")
{
    constexpr Camera camera{Pointf{0.0f, 0.0f, 500.0f},
                            Vectorf{0.0f},
                            Vectorf{0.0f, 1.0f, 0.0f},
                            500.0f};
    auto result = camera.get_ray_direction(Pointf{0.0f});

    REQUIRE(result == Vectorf{0.0f, 0.0f, -1.0f});
}
