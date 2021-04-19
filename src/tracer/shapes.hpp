#pragma once

#include "ray.hpp"
#include "utils.hpp"

#include <optional>
#include <variant>

struct ShadeRec
{
    static constexpr int max_reflection_depth{12};

    Point hit_point{};
    Vector normal{};
    Colour default_colour{0.0f};
    Ray ray;
    int material_id{-1};
    int reflection_depth{0};
};

template<typename T>
class Shape : public utils::StaticBase<T, Shape>
{
public:
    constexpr Shape()
    {}

    static constexpr float epsilon{0.01f};
    constexpr std::optional<ShadeRec> hit(Ray const& ray) const
    {
        return this->self().hit(ray);
    }

    constexpr std::optional<float> shadow_hit(Ray const& ray) const
    {
        return this->self().shadow_hit(ray);
    }

    constexpr void set_default_colour(Colour const& colour)
    {
        m_default_colour = colour;
    }

    constexpr void set_material_id(int id)
    {
        m_material_id = id;
    }

protected:
    Colour m_default_colour;
    int m_material_id{-1};
};

class EmptyShape : public Shape<EmptyShape>
{
public:
    constexpr std::optional<ShadeRec> hit(Ray const&) const
    {
        return {};
    }

    constexpr std::optional<float> shadow_hit(Ray const&) const
    {
        return {};
    }
};

class Plane : public Shape<Plane>
{
public:
    constexpr Plane() : m_pt{}, m_normal{0.0f, 1.0f, 0.0f}
    {}

    constexpr Plane(Point const& pt, Vector const& n) : m_pt{pt}, m_normal{n}
    {}

    constexpr std::optional<ShadeRec> hit(Ray const& ray) const
    {
        Vector u = m_pt - ray.origin;
        float t  = dot(u, m_normal) / dot(ray.direction, m_normal);

        if (t > epsilon)
        {
            ShadeRec rec;
            rec.normal         = m_normal;
            rec.hit_point      = ray(t);
            rec.default_colour = m_default_colour;
            rec.material_id    = m_material_id;
            rec.ray            = ray;
            return {rec};
        }

        return {};
    }

    constexpr std::optional<float> shadow_hit(Ray const& ray) const
    {
        Vector u = m_pt - ray.origin;
        float t  = dot(u, m_normal) / dot(ray.direction, m_normal);

        if (t > epsilon)
        {
            return {t};
        }

        return {std::nullopt};
    }

private:
    Point m_pt;
    Vector m_normal;
};

class Sphere : public Shape<Sphere>
{
public:
    constexpr Sphere() : m_centre{0.0f}, m_radius{1.0f}, m_radius_squared{1.0f}
    {}

    constexpr Sphere(Point const& pt, float radius) :
        m_centre{pt}, m_radius{radius}, m_radius_squared{radius * radius}
    {}

    constexpr std::optional<ShadeRec> hit(Ray const& ray) const
    {
        Vector temp = ray.origin - m_centre;
        float a     = dot(ray.direction, ray.direction);
        float b     = 2.0f * dot(temp, ray.direction);
        float c     = dot(temp, temp) - m_radius_squared;
        float disc  = b * b - 4.0f * a * c;

        if (disc > 0.0f)
        {
            float e     = utils::sqrt(disc);
            float denom = 2.0f * a;
            float t_min{0.0f};
            bool hit{false};

            float t = (-b - e) / denom;
            if (t > epsilon)
            {
                hit   = true;
                t_min = t;
            }

            t = (-b + e) / denom;
            if (!hit && t > epsilon)
            {
                hit   = true;
                t_min = t;
            }

            if (hit)
            {
                ShadeRec rec;
                rec.normal         = (temp + t_min * ray.direction) / m_radius;
                rec.hit_point      = ray(t_min);
                rec.default_colour = m_default_colour;
                rec.material_id    = m_material_id;
                rec.ray            = ray;
                return {rec};
            }
        }

        return {};
    }

    constexpr std::optional<float> shadow_hit(Ray const& ray) const
    {
        Vector temp = ray.origin - m_centre;
        float a     = dot(ray.direction, ray.direction);
        float b     = 2.0f * dot(temp, ray.direction);
        float c     = dot(temp, temp) - m_radius_squared;
        float disc  = b * b - 4.0f * a * c;

        if (disc > 0.0f)
        {
            float e     = utils::sqrt(disc);
            float denom = 2.0f * a;

            float t = (-b - e) / denom;
            if (t > epsilon)
            {
                return {t};
            }

            t = (-b + e) / denom;
            if (t > epsilon)
            {
                return {t};
            }
        }

        return {std::nullopt};
    }

private:
    Point m_centre;
    float m_radius;
    float m_radius_squared;
};

template<class... Shapes>
class ShapeWrapper
{
public:
    constexpr ShapeWrapper()
    {}

    template<typename T, typename = utils::Contains<T, Shapes...>>
    constexpr ShapeWrapper(T&& elem) : m_shape{std::forward<T>(elem)}
    {}

    constexpr std::optional<ShadeRec> hit(Ray const& ray) const
    {
        return std::visit([ray](auto const& elem) { return elem.hit(ray); },
                          m_shape);
    }

    constexpr std::optional<float> shadow_hit(Ray const& ray) const
    {
        return std::visit(
            [ray](auto const& elem) { return elem.shadow_hit(ray); }, m_shape);
    }

private:
    std::variant<Shapes...> m_shape;
};

using Shapes = ShapeWrapper<EmptyShape, Plane, Sphere>;
