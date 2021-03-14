#include "ray.hpp"

#include <catch2/catch.hpp>

TEST_CASE("[Ray] - constructor: empty constructor")
{
    constexpr math::Rayf ray{};

    REQUIRE(ray.origin == math::Vectorf{0.0f});
    REQUIRE(ray.direction == math::Vectorf{0.0f});
}

TEST_CASE("[Ray] - constructor: parameterized constructor")
{
    constexpr math::Rayf ray{math::Pointf{0.0f}, math::Vectorf{1.0f}};

    REQUIRE(ray.origin == math::Vectorf{0.0f});
    REQUIRE(ray.direction == math::Vectorf{1.0f});
}

TEST_CASE("[Ray] - operator()")
{
    constexpr math::Rayf ray{math::Pointf{0.0f}, math::Vectorf{1.0f}};
    auto result = ray(1.0f);

    REQUIRE(result == math::Vectorf{1.0f});
}
