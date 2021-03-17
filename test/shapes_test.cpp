#include "shapes.hpp"

#include <catch2/catch.hpp>

TEST_CASE("[Plane] - hit: default plane")
{
    SECTION("Ray intersects")
    {
        constexpr Plane p;
        constexpr Rayf ray{Pointf{0.0f, 1.0f, 0.0f},
                           Vectorf{0.0f, -1.0f, 0.0f}};

        constexpr auto result = p.hit(ray);

        REQUIRE(result.has_value());
    }

    SECTION("Ray misses")
    {
        constexpr Plane p;
        constexpr Rayf ray{Pointf{0.0f, 1.0f, 0.0f}, Vectorf{0.0f, 1.0f, 0.0f}};

        constexpr auto result = p.hit(ray);

        REQUIRE_FALSE(result.has_value());
    }
}

TEST_CASE("[Plane] - hit: custom plane")
{
    SECTION("Ray intersects")
    {
        constexpr Plane p{Pointf{0.0f}, Vectorf{1.0f, 0.0f, 0.0f}};
        constexpr Rayf ray{Pointf{1.0f, 0.0f, 0.0f},
                           Vectorf{-1.0f, 1.0f, 0.0f}};

        constexpr auto result = p.hit(ray);

        REQUIRE(result.has_value());
    }

    SECTION("Ray misses")
    {
        constexpr Plane p{Pointf{0.0f}, Vectorf{1.0f, 0.0f, 0.0f}};
        constexpr Rayf ray{Pointf{1.0f, 0.0f, 0.0f}, Vectorf{1.0f, 1.0f, 0.0f}};

        constexpr auto result = p.hit(ray);

        REQUIRE_FALSE(result.has_value());
    }
}

TEST_CASE("[Sphere] - hit: default sphere")
{
    SECTION("Ray intersects")
    {
        constexpr Sphere s;
        constexpr Rayf ray{Pointf{2.0f, 0.0f, 0.0f},
                           Vectorf{-1.0f, 0.0f, 0.0f}};

        constexpr auto result = s.hit(ray);

        REQUIRE(result.has_value());
    }

    SECTION("Ray misses")
    {
        constexpr Sphere s;
        constexpr Rayf ray{Pointf{2.0f, 0.0f, 0.0f}, Vectorf{1.0f, 0.0f, 0.0f}};

        constexpr auto result = s.hit(ray);

        REQUIRE_FALSE(result.has_value());
    }
}

TEST_CASE("[Sphere] - hit: custom sphere")
{
    SECTION("Ray intersects")
    {
        constexpr Sphere s{Pointf{1.0f, 0.0f, 0.0f}, 2.0f};
        constexpr Rayf ray{Pointf{5.0f, 0.0f, 0.0f},
                           Vectorf{-1.0f, 0.0f, 0.0f}};

        constexpr auto result = s.hit(ray);

        REQUIRE(result.has_value());
    }

    SECTION("Ray misses")
    {
        constexpr Sphere s{Pointf{1.0f, 0.0f, 0.0f}, 2.0f};
        constexpr Rayf ray{Pointf{5.0f, 0.0f, 0.0f}, Vectorf{1.0f, 0.0f, 0.0f}};

        constexpr auto result = s.hit(ray);

        REQUIRE_FALSE(result.has_value());
    }
}

TEST_CASE("[ShapeWrapper] - hit: plane")
{
    constexpr Shapes shapes{Plane{}};
    constexpr Rayf ray{Pointf{0.0f, 1.0f, 0.0f}, Vectorf{0.0f, -1.0f, 0.0f}};

    constexpr auto result = shapes.hit(ray);

    REQUIRE(result.has_value());
}

TEST_CASE("[ShapeWrapper] - hit: sphere")
{
    constexpr Shapes shapes{Sphere{}};
    constexpr Rayf ray{Pointf{2.0f, 0.0f, 0.0f}, Vectorf{-1.0f, 0.0f, 0.0f}};

    constexpr auto result = shapes.hit(ray);

    REQUIRE(result.has_value());
}

TEST_CASE("[ShapeContainer] - hit")
{
    constexpr std::array<Shapes, 2> list{Sphere{}, Plane{}};
    constexpr ShapeContainer<decltype(list)> container{std::move(list)};
    constexpr Rayf ray{Pointf{2.0f, 0.0f, 0.0f}, Vectorf{-1.0f, 0.0f, 0.0f}};

    constexpr auto result = container.hit(ray);

    REQUIRE(result.has_value());
}
