#include "shapes.hpp"

#include <catch2/catch.hpp>

TEST_CASE("[Plane] - hit: default plane")
{
    SECTION("Ray intersects")
    {
        constexpr Plane p;
        constexpr Ray ray{Point{0.0f, 1.0f, 0.0f}, Vector{0.0f, -1.0f, 0.0f}};

        constexpr auto result = p.hit(ray);

        REQUIRE(result.has_value());
    }

    SECTION("Ray misses")
    {
        constexpr Plane p;
        constexpr Ray ray{Point{0.0f, 1.0f, 0.0f}, Vector{0.0f, 1.0f, 0.0f}};

        constexpr auto result = p.hit(ray);

        REQUIRE_FALSE(result.has_value());
    }
}

TEST_CASE("[Plane] - hit: custom plane")
{
    SECTION("Ray intersects")
    {
        constexpr Plane p{Point{0.0f}, Vector{1.0f, 0.0f, 0.0f}};
        constexpr Ray ray{Point{1.0f, 0.0f, 0.0f}, Vector{-1.0f, 1.0f, 0.0f}};

        constexpr auto result = p.hit(ray);

        REQUIRE(result.has_value());
    }

    SECTION("Ray misses")
    {
        constexpr Plane p{Point{0.0f}, Vector{1.0f, 0.0f, 0.0f}};
        constexpr Ray ray{Point{1.0f, 0.0f, 0.0f}, Vector{1.0f, 1.0f, 0.0f}};

        constexpr auto result = p.hit(ray);

        REQUIRE_FALSE(result.has_value());
    }
}

TEST_CASE("[Sphere] - hit: default sphere")
{
    SECTION("Ray intersects")
    {
        constexpr Sphere s;
        constexpr Ray ray{Point{2.0f, 0.0f, 0.0f}, Vector{-1.0f, 0.0f, 0.0f}};

        constexpr auto result = s.hit(ray);

        REQUIRE(result.has_value());
    }

    SECTION("Ray misses")
    {
        constexpr Sphere s;
        constexpr Ray ray{Point{2.0f, 0.0f, 0.0f}, Vector{1.0f, 0.0f, 0.0f}};

        constexpr auto result = s.hit(ray);

        REQUIRE_FALSE(result.has_value());
    }
}

TEST_CASE("[Sphere] - hit: custom sphere")
{
    SECTION("Ray intersects")
    {
        constexpr Sphere s{Point{1.0f, 0.0f, 0.0f}, 2.0f};
        constexpr Ray ray{Point{5.0f, 0.0f, 0.0f}, Vector{-1.0f, 0.0f, 0.0f}};

        constexpr auto result = s.hit(ray);

        REQUIRE(result.has_value());
    }

    SECTION("Ray misses")
    {
        constexpr Sphere s{Point{1.0f, 0.0f, 0.0f}, 2.0f};
        constexpr Ray ray{Point{5.0f, 0.0f, 0.0f}, Vector{1.0f, 0.0f, 0.0f}};

        constexpr auto result = s.hit(ray);

        REQUIRE_FALSE(result.has_value());
    }
}

TEST_CASE("[ShapeWrapper] - hit: plane")
{
    constexpr Shapes shapes{Plane{}};
    constexpr Ray ray{Point{0.0f, 1.0f, 0.0f}, Vector{0.0f, -1.0f, 0.0f}};

    constexpr auto result = shapes.hit(ray);

    REQUIRE(result.has_value());
}

TEST_CASE("[ShapeWrapper] - hit: sphere")
{
    constexpr Shapes shapes{Sphere{}};
    constexpr Ray ray{Point{2.0f, 0.0f, 0.0f}, Vector{-1.0f, 0.0f, 0.0f}};

    constexpr auto result = shapes.hit(ray);

    REQUIRE(result.has_value());
}

TEST_CASE("[ShapeContainer] - hit")
{
    constexpr std::array<Shapes, 2> list{Sphere{}, Plane{}};
    constexpr ShapeContainer<decltype(list)> container{std::move(list)};
    constexpr Ray ray{Point{2.0f, 0.0f, 0.0f}, Vector{-1.0f, 0.0f, 0.0f}};

    constexpr auto result = container.hit(ray);

    REQUIRE(result.has_value());
}
