#include "utils.hpp"

#include <catch2/catch.hpp>
#include <cmath>
#include <fmt/printf.h>

template<typename T>
constexpr bool is_nan(T x)
{
    return std::isnan(x);
}

TEST_CASE("[math] - sqrt: negative number")
{
    constexpr float x{-1.0f};
    constexpr auto result = utils::sqrt(x);

    REQUIRE(is_nan(result));
}

TEST_CASE("[math] - sqrt: infinity")
{
    constexpr float x{std::numeric_limits<float>::infinity()};
    constexpr auto result = utils::sqrt(x);

    REQUIRE(is_nan(result));
}

TEST_CASE("[math] - sqrt: valid number")
{
    constexpr float x{4.0f};
    constexpr auto result = utils::sqrt(x);

    REQUIRE(result == 2.0f);
}
