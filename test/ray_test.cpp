#include "ray.hpp"

#include <catch2/catch.hpp>

TEST_CASE("[Ray] - constructor: empty constructor")
{
    constexpr Rayf ray{};

    REQUIRE(ray.origin == Vectorf{0.0f});
    REQUIRE(ray.direction == Vectorf{0.0f});
}

TEST_CASE("[Ray] - constructor: parameterized constructor")
{
    constexpr Rayf ray{Pointf{0.0f}, Vectorf{1.0f}};

    REQUIRE(ray.origin == Vectorf{0.0f});
    REQUIRE(ray.direction == Vectorf{1.0f});
}

TEST_CASE("[Ray] - operator()")
{
    constexpr Rayf ray{Pointf{0.0f}, Vectorf{1.0f}};
    auto result = ray(1.0f);

    REQUIRE(result == Vectorf{1.0f});
}
