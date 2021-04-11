#pragma once

#include "shapes.hpp"
#include "utils.hpp"

#include <variant>

template<typename T>
class Light : public utils::StaticBase<T, Light>
{
public:
    constexpr Vector get_direction(ShadeRec const& rec) const
    {
        return this->self().get_direction(rec);
    }

    constexpr Colour l(ShadeRec const&) const
    {
        return m_radiance * m_colour;
    }

    constexpr void set_radiance(float r)
    {
        m_radiance = r;
    }

    constexpr void set_colour(Colour const& cl)
    {
        m_colour = cl;
    }

    constexpr void set_casts_shadows(bool casts)
    {
        m_casts_shadows = casts;
    }

    constexpr bool casts_shadows() const
    {
        return m_casts_shadows;
    }

    constexpr Point get_position() const
    {
        return this->self().get_position();
    }

protected:
    Colour m_colour{1.0f};
    float m_radiance{1.0f};
    bool m_casts_shadows{false};
};

class AmbientLight : public Light<AmbientLight>
{
public:
    constexpr Vector get_direction(ShadeRec const&) const
    {
        return Vector{0.0f};
    }

    constexpr Point get_position() const
    {
        return {};
    }
};

class DirectionalLight : public Light<DirectionalLight>
{
public:
    constexpr Vector get_direction(ShadeRec const&) const
    {
        return m_direction;
    }

    constexpr void set_direction(Vector const& dir)
    {
        m_direction = normalise(dir);
    }

    constexpr Point get_position() const
    {
        return {};
    }

private:
    Vector m_direction;
};

class PointLight : public Light<PointLight>
{
public:
    constexpr Vector get_direction(ShadeRec const& rec) const
    {
        return normalise(m_position - rec.hit_point);
    }

    constexpr void set_position(Point const& pt)
    {
        m_position = pt;
    }

    constexpr Point get_position() const
    {
        return m_position;
    }

private:
    Point m_position;
};

template<class... Lights>
class LightWrapper
{
public:
    constexpr LightWrapper()
    {}

    template<typename T, typename = utils::Contains<T, Lights...>>
    constexpr LightWrapper(T&& elem) : m_light{std::forward<T>(elem)}
    {}

    constexpr Vector get_direction(ShadeRec const& rec) const
    {
        return std::visit(
            [rec](auto const& elem) { return elem.get_direction(rec); },
            m_light);
    }

    constexpr Colour l(ShadeRec const& rec) const
    {
        return std::visit([rec](auto const& elem) { return elem.l(rec); },
                          m_light);
    }

    constexpr bool casts_shadows() const
    {
        return std::visit([](auto const& elem) { return elem.casts_shadows(); },
                          m_light);
    }

    constexpr Point get_position() const
    {
        return std::visit([](auto const& elem) { return elem.get_position(); },
                          m_light);
    }

private:
    std::variant<Lights...> m_light;
};

using Lights = LightWrapper<AmbientLight, PointLight, DirectionalLight>;
