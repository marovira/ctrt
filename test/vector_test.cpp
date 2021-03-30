#include "vector.hpp"

#include <catch2/catch.hpp>
#include <fmt/printf.h>

TEST_CASE("[Vector] - constructor: empty constructor")
{
    constexpr Vector v;
    REQUIRE(v.x() == 0.0f);
    REQUIRE(v.y() == 0.0f);
    REQUIRE(v.z() == 0.0f);
}

TEST_CASE("[Vector] - constructor: uniform constructor")
{
    constexpr Vector v{1.0f};
    REQUIRE(v.x() == 1.0f);
    REQUIRE(v.y() == 1.0f);
    REQUIRE(v.z() == 1.0f);
}

TEST_CASE("[Vector] - constructor: parametrized constructor")
{
    constexpr Vector v{1.0f, 2.0f, 3.0f};
    REQUIRE(v.x() == 1.0f);
    REQUIRE(v.y() == 2.0f);
    REQUIRE(v.z() == 3.0f);
}

TEST_CASE("[Vector] - operator[]: non-const")
{
    constexpr Vector v{1.0f, 2.0f, 3.0f};
    REQUIRE(v[0] == 1.0f);
    REQUIRE(v[1] == 2.0f);
    REQUIRE(v[2] == 3.0f);
}

TEST_CASE("[Vector] - operator[]: const")
{
    constexpr Vector v{1.0f, 2.0f, 3.0f};
    REQUIRE(v[0] == 1.0f);
    REQUIRE(v[1] == 2.0f);
    REQUIRE(v[2] == 3.0f);
}

TEST_CASE("[Vector] - operator==")
{
    constexpr Vector v{1.0f};
    constexpr Vector u{2.0f};

    REQUIRE(v == v);
    REQUIRE_FALSE(v == u);
}

TEST_CASE("[Vector] - operator!=")
{
    constexpr Vector v{1.0f};
    constexpr Vector u{2.0f};

    REQUIRE(v != u);
    REQUIRE_FALSE(v != v);
}

TEST_CASE("[Vector] - operator-: unary")
{
    constexpr Vector v{1.0f};
    constexpr auto result = -v;

    REQUIRE(result.x() == -1.0f);
    REQUIRE(result.y() == -1.0f);
    REQUIRE(result.z() == -1.0f);
}

TEST_CASE("[Vector] - operator +=")
{
    Vector v{1.0f};
    Vector u{2.0f};

    v += u;

    REQUIRE(v.x() == 3.0f);
    REQUIRE(v.y() == 3.0f);
    REQUIRE(v.z() == 3.0f);
}

TEST_CASE("[Vector] - operator-=")
{
    Vector v{1.0f};
    Vector u{2.0f};

    u -= v;

    REQUIRE(u.x() == 1.0f);
    REQUIRE(u.y() == 1.0f);
    REQUIRE(u.z() == 1.0f);
}

TEST_CASE("[Vector] - operator*=")
{
    Vector v{1.0f};
    v *= 2.0f;

    REQUIRE(v.x() == 2.0f);
    REQUIRE(v.y() == 2.0f);
    REQUIRE(v.z() == 2.0f);
}

TEST_CASE("[Vector] - operator/=")
{
    Vector v{2.0f};
    v /= 2.0f;

    REQUIRE(v.x() == 1.0f);
    REQUIRE(v.y() == 1.0f);
    REQUIRE(v.z() == 1.0f);
}

TEST_CASE("[Vector] - operator+")
{
    constexpr Vector v{1.0f};
    constexpr Vector u{2.0f};

    constexpr auto result = v + u;

    REQUIRE(result.x() == 3.0f);
    REQUIRE(result.y() == 3.0f);
    REQUIRE(result.z() == 3.0f);
}

TEST_CASE("[Vector] - operator-: binary")
{
    constexpr Vector v{1.0f};
    constexpr Vector u{2.0f};

    constexpr auto result = u - v;

    REQUIRE(result.x() == 1.0f);
    REQUIRE(result.y() == 1.0f);
    REQUIRE(result.z() == 1.0f);
}

TEST_CASE("[Vector] - operator*: vector * vector")
{
    constexpr Vector v{1.0f};
    constexpr Vector u{2.0f};

    constexpr auto result = v * u;

    REQUIRE(result.x() == 2.0f);
    REQUIRE(result.y() == 2.0f);
    REQUIRE(result.z() == 2.0f);
}

TEST_CASE("[Vector] - operator*: vector * scalar")
{
    constexpr Vector v{1.0f};

    constexpr auto result = v * 2.0f;

    REQUIRE(result.x() == 2.0f);
    REQUIRE(result.y() == 2.0f);
    REQUIRE(result.z() == 2.0f);
}

TEST_CASE("[Vector] - oeprator*: scalar * vector")
{
    constexpr Vector v{1.0f};

    constexpr auto result = 2.0f * v;

    REQUIRE(result.x() == 2.0f);
    REQUIRE(result.y() == 2.0f);
    REQUIRE(result.z() == 2.0f);
}

TEST_CASE("[Vector] - operator/")
{
    constexpr Vector v{2.0f};

    constexpr auto result = v / 2.0f;

    REQUIRE(result.x() == 1.0f);
    REQUIRE(result.y() == 1.0f);
    REQUIRE(result.z() == 1.0f);
}

TEST_CASE("[Vector] - dot")
{
    constexpr Vector v{1.0f};
    constexpr Vector u{2.0f};

    constexpr auto result = dot(v, u);

    REQUIRE(result == 6.0f);
}

TEST_CASE("[Vector] - length")
{
    constexpr Vector v{2.0f, 0.0f, 0.0};

    constexpr auto result = length(v);

    REQUIRE(result == 2.0f);
}

TEST_CASE("[Vector] - length_squared")
{
    constexpr Vector v{2.0f, 0.0f, 0.0};

    constexpr auto result = length_squared(v);

    REQUIRE(result == 4.0f);
}

TEST_CASE("[Vector] - cross")
{
    constexpr Vector v{1.0f, 0.0f, 0.0f};
    constexpr Vector u{0.0f, 1.0f, 0.0f};

    constexpr auto w = cross(v, u);

    REQUIRE(w.x() == 0.0f);
    REQUIRE(w.y() == 0.0f);
    REQUIRE(w.z() == 1.0f);
}

TEST_CASE("[Vector] - normalise")
{
    constexpr Vector v{2.0f, 0.0f, 0.0f};

    constexpr auto result = normalise(v);

    REQUIRE(result.x() == 1.0f);
    REQUIRE(result.y() == 0.0f);
    REQUIRE(result.z() == 0.0f);
}
