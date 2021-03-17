#include "materials.hpp"

#include <catch2/catch.hpp>

TEST_CASE("[DefaultMaterial] - shade")
{
    constexpr ShadeRec rc;
    constexpr DefaultMaterial mat;
    constexpr Colourf result = mat.shade(rc);

    REQUIRE(result == Colourf{1.0f, 0.0f, 0.0f});
}

TEST_CASE("[MaterialWrapper] - shade: default material")
{
    constexpr Materials materials{DefaultMaterial{}};
    constexpr Colourf result = materials.shade(ShadeRec{});

    REQUIRE(result == Colourf{1.0f, 0.0f, 0.0f});
}

TEST_CASE("[MaterialContainer] - operator[]: const")
{
    constexpr std::array<Materials, 1> list{DefaultMaterial{}};
    constexpr MaterialContainer<decltype(list)> container{std::move(list)};

    constexpr ShadeRec rc{};
    constexpr Colourf result = container[0].shade(rc);
    REQUIRE(result == Colourf{1.0f, 0.0f, 0.0f});
}
