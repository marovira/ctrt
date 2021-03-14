#include "vector.hpp"

#include <catch2/catch.hpp>
#include <fmt/printf.h>

TEST_CASE("[Vector] - constructor: empty constructor")
{
    constexpr math::Vectorf v;
    REQUIRE(v.x() == 0.0f);
    REQUIRE(v.y() == 0.0f);
    REQUIRE(v.z() == 0.0f);
}

TEST_CASE("[Vector] - constructor: uniform constructor")
{
    constexpr math::Vectorf v{1.0f};
    REQUIRE(v.x() == 1.0f);
    REQUIRE(v.y() == 1.0f);
    REQUIRE(v.z() == 1.0f);
}

TEST_CASE("[Vector] - constructor: parametrized constructor")
{
    constexpr math::Vectorf v{1.0f, 2.0f, 3.0f};
    REQUIRE(v.x() == 1.0f);
    REQUIRE(v.y() == 2.0f);
    REQUIRE(v.z() == 3.0f);
}

TEST_CASE("[Vector] - operator[]: non-const")
{
    constexpr math::Vectorf v{1.0f, 2.0f, 3.0f};
    REQUIRE(v[0] == 1.0f);
    REQUIRE(v[1] == 2.0f);
    REQUIRE(v[2] == 3.0f);
}

TEST_CASE("[Vector] - operator[]: const")
{
    constexpr math::Vectorf v{1.0f, 2.0f, 3.0f};
    REQUIRE(v[0] == 1.0f);
    REQUIRE(v[1] == 2.0f);
    REQUIRE(v[2] == 3.0f);
}

TEST_CASE("[Vector] - unary_op: rvalue version")
{
    constexpr math::Vectorf v{1.0f};
    constexpr auto result =
        math::unary_op(std::move(v), [](float a) { return a; });

    REQUIRE(result.x() == 1.0f);
    REQUIRE(result.y() == 1.0f);
    REQUIRE(result.z() == 1.0f);
}

TEST_CASE("[Vector] - unary_op: lvalue version")
{
    constexpr math::Vectorf v{1.0f};
    constexpr auto result = math::unary_op(v, [](float a) { return a; });

    REQUIRE(result.x() == 1.0f);
    REQUIRE(result.y() == 1.0f);
    REQUIRE(result.z() == 1.0f);
}

TEST_CASE("[Vector] - binary_op: rvalue version")
{
    constexpr math::Vectorf v{1.0f};
    constexpr math::Vectorf u{2.0f};
    constexpr auto result = math::binary_op(
        std::move(v), u, [](float a, float b) { return a + b; });

    REQUIRE(result.x() == 3.0f);
    REQUIRE(result.y() == 3.0f);
    REQUIRE(result.z() == 3.0f);
}

TEST_CASE("[Vector] - binary_op: lvalue version")
{
    constexpr math::Vectorf v{1.0f};
    constexpr math::Vectorf u{2.0f};
    constexpr auto result =
        math::binary_op(v, u, [](float a, float b) { return a + b; });

    REQUIRE(result.x() == 3.0f);
    REQUIRE(result.y() == 3.0f);
    REQUIRE(result.z() == 3.0f);
}

TEST_CASE("[Vector] - operator-: unary")
{
    constexpr math::Vectorf v{1.0f};
    constexpr auto result = -v;

    REQUIRE(result.x() == -1.0f);
    REQUIRE(result.y() == -1.0f);
    REQUIRE(result.z() == -1.0f);
}

TEST_CASE("[Vector] - operator +=")
{
    math::Vectorf v{1.0f};
    math::Vectorf u{2.0f};

    v += u;

    REQUIRE(v.x() == 3.0f);
    REQUIRE(v.y() == 3.0f);
    REQUIRE(v.z() == 3.0f);
}

TEST_CASE("[Vector] - operator-=")
{
    math::Vectorf v{1.0f};
    math::Vectorf u{2.0f};

    u -= v;

    REQUIRE(u.x() == 1.0f);
    REQUIRE(u.y() == 1.0f);
    REQUIRE(u.z() == 1.0f);
}

TEST_CASE("[Vector] - operator*=")
{
    math::Vectorf v{1.0f};
    v *= 2.0f;

    REQUIRE(v.x() == 2.0f);
    REQUIRE(v.y() == 2.0f);
    REQUIRE(v.z() == 2.0f);
}

TEST_CASE("[Vector] - operator/=")
{
    math::Vectorf v{2.0f};
    v /= 2.0f;

    REQUIRE(v.x() == 1.0f);
    REQUIRE(v.y() == 1.0f);
    REQUIRE(v.z() == 1.0f);
}

TEST_CASE("[Vector] - operator+")
{
    constexpr math::Vectorf v{1.0f};
    constexpr math::Vectorf u{2.0f};

    constexpr auto result = v + u;

    REQUIRE(result.x() == 3.0f);
    REQUIRE(result.y() == 3.0f);
    REQUIRE(result.z() == 3.0f);
}

TEST_CASE("[Vector] - operator-: binary")
{
    constexpr math::Vectorf v{1.0f};
    constexpr math::Vectorf u{2.0f};

    constexpr auto result = u - v;

    REQUIRE(result.x() == 1.0f);
    REQUIRE(result.y() == 1.0f);
    REQUIRE(result.z() == 1.0f);
}

TEST_CASE("[Vector] - operator*: vector * vector")
{
    constexpr math::Vectorf v{1.0f};
    constexpr math::Vectorf u{2.0f};

    constexpr auto result = v * u;

    REQUIRE(result.x() == 2.0f);
    REQUIRE(result.y() == 2.0f);
    REQUIRE(result.z() == 2.0f);
}

TEST_CASE("[Vector] - operator*: vector * scalar")
{
    constexpr math::Vectorf v{1.0f};

    constexpr auto result = v * 2.0f;

    REQUIRE(result.x() == 2.0f);
    REQUIRE(result.y() == 2.0f);
    REQUIRE(result.z() == 2.0f);
}

TEST_CASE("[Vector] - oeprator*: scalar * vector")
{
    constexpr math::Vectorf v{1.0f};

    constexpr auto result = 2.0f * v;

    REQUIRE(result.x() == 2.0f);
    REQUIRE(result.y() == 2.0f);
    REQUIRE(result.z() == 2.0f);
}

TEST_CASE("[Vector] - operator/")
{
    constexpr math::Vectorf v{2.0f};

    constexpr auto result = v / 2.0f;

    REQUIRE(result.x() == 1.0f);
    REQUIRE(result.y() == 1.0f);
    REQUIRE(result.z() == 1.0f);
}

TEST_CASE("[Vector] - dot")
{
    constexpr math::Vectorf v{1.0f};
    constexpr math::Vectorf u{2.0f};

    constexpr auto result = math::dot(v, u);

    REQUIRE(result == 6.0f);
}

TEST_CASE("[Vector] - length")
{
    constexpr math::Vectorf v{2.0f, 0.0f, 0.0};

    constexpr auto result = math::length(v);

    REQUIRE(result == 2.0f);
}

TEST_CASE("[Vector] - length_squared")
{
    constexpr math::Vectorf v{2.0f, 0.0f, 0.0};

    constexpr auto result = math::length_squared(v);

    REQUIRE(result == 4.0f);
}

TEST_CASE("[Vector] - cross")
{
    constexpr math::Vectorf v{1.0f, 0.0f, 0.0f};
    constexpr math::Vectorf u{0.0f, 1.0f, 0.0f};

    constexpr auto w = math::cross(v, u);

    REQUIRE(w.x() == 0.0f);
    REQUIRE(w.y() == 0.0f);
    REQUIRE(w.z() == 1.0f);
}

TEST_CASE("[Vector] - unit_vector")
{
    constexpr math::Vectorf v{2.0f, 0.0f, 0.0f};

    constexpr auto result = unit_vector(v);

    REQUIRE(result.x() == 1.0f);
    REQUIRE(result.y() == 0.0f);
    REQUIRE(result.z() == 0.0f);
}
