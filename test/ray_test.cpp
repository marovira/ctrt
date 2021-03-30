#include "ray.hpp"

#include <catch2/catch.hpp>

TEST_CASE("[Ray] - constructor: empty constructor")
{
    constexpr Ray ray{};

    REQUIRE(ray.origin == Vector{0.0f});
    REQUIRE(ray.direction == Vector{0.0f});
}

TEST_CASE("[Ray] - constructor: parameterized constructor")
{
    constexpr Ray ray{Point{0.0f}, Vector{1.0f}};

    REQUIRE(ray.origin == Vector{0.0f});
    REQUIRE(ray.direction == Vector{1.0f});
}

TEST_CASE("[Ray] - operator()")
{
    constexpr Ray ray{Point{0.0f}, Vector{1.0f}};
    auto result = ray(1.0f);

    REQUIRE(result == Vector{1.0f});
}
