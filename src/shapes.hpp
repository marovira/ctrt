#pragma once

#include "ray.hpp"
#include "utils.hpp"

#include <optional>
#include <variant>

struct ShadeRec
{
    Point hit_point{};
    Vector normal{};
    int material_id{0};
    float t_min{0.0f};
};

template<typename T>
class Shape : public utils::StaticBase<T, Shape>
{
public:
    static constexpr float epsilon{0.0001f};
    constexpr std::optional<ShadeRec> hit(Ray const& ray) const
    {
        return this->self().hit(ray);
    }

    constexpr void set_material(int id)
    {
        m_material_id = id;
    }

protected:
    int m_material_id{0};
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
            rec.normal      = m_normal;
            rec.hit_point   = ray(t);
            rec.material_id = m_material_id;
            rec.t_min       = t;
            return {rec};
        }

        return {};
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

        if (disc < 0.0f)
        {
            return {};
        }
        else
        {
            float e     = utils::sqrt(disc);
            float denom = 2.0f * a;

            // Smaller root first.
            float t = (-b - e) / denom;
            if (t > epsilon)
            {
                ShadeRec rec;
                rec.t_min       = t;
                rec.normal      = (temp + t * ray.direction) / m_radius;
                rec.hit_point   = ray(t);
                rec.material_id = m_material_id;
                return {rec};
            }

            // Now the larger root.
            t = (-b + e) / denom;
            if (t > epsilon)
            {
                ShadeRec rec;
                rec.t_min       = t;
                rec.normal      = (temp + t * ray.direction) / m_radius;
                rec.hit_point   = ray(t);
                rec.material_id = m_material_id;
                return {rec};
            }
        }

        return {};
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
    template<typename T, typename = utils::Contains<T, Shapes...>>
    constexpr ShapeWrapper(T&& elem) : m_shape{std::forward<T>(elem)}
    {}

    constexpr std::optional<ShadeRec> hit(Ray const& ray) const
    {
        return std::visit([ray](auto const& elem) { return elem.hit(ray); },
                          m_shape);
    }

private:
    std::variant<Shapes...> m_shape;
};

using Shapes = ShapeWrapper<Plane, Sphere>;

template<typename Container>
class ShapeContainer
{
public:
    constexpr ShapeContainer(Container&& list) :
        m_shapes{std::forward<Container>(list)}
    {}

    constexpr std::optional<ShadeRec> hit(Ray const& ray) const
    {
        for (auto const& elem : m_shapes)
        {
            if (auto result = elem.hit(ray); result)
            {
                return result;
            }
        }

        return {};
    }

private:
    Container m_shapes;
};
