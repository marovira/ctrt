#pragma once

#include "camera.hpp"
#include "materials.hpp"
#include "ray.hpp"
#include "shapes.hpp"
#include "utils.hpp"
#include "vector.hpp"

template<typename T>
class Scene : public utils::StaticBase<T, Scene>
{
public:
    constexpr void set_camera(Camera const& camera)
    {
        m_camera = camera;
    }

    constexpr Camera get_camera() const
    {
        return m_camera;
    }

    template<class ShapeContainer, class MaterialContainer>
    constexpr Colour trace(Ray const& ray,
                           ShapeContainer const& shapes,
                           MaterialContainer const& materials) const
    {
        return this->self().trace(ray, shapes, materials);
    }

    constexpr Colour trace_simple(Ray const& ray) const
    {
        return this->self().trace_simple(ray);
    }

    constexpr Colour background(Ray const& ray) const
    {
        return this->self().background(ray);
    }

private:
    Camera m_camera;
};

class FirstScene : public Scene<FirstScene>
{
public:
    constexpr FirstScene() = default;

    constexpr Colour trace_simple(Ray const& ray) const
    {
        return background(ray);
    }

    constexpr Colour background(Ray const& ray) const
    {
        float t = 0.5f * (ray.direction.y() + 1.0f);
        return (1.0f - t) * Colour{1.0f, 1.0f, 1.0f} +
               t * Colour{0.5f, 0.7f, 1.0f};
    }
};

class SphereScene : public Scene<SphereScene>
{
public:
    constexpr SphereScene() = default;

    template<class ShapeContainer, class MaterialContainer>
    constexpr Colour trace(Ray const& ray,
                           ShapeContainer const& shapes,
                           MaterialContainer const& materials) const
    {
        for (auto const& shape : shapes)
        {
            if (auto result = shape.hit(ray); result)
            {
                ShadeRec rc = *result;
                return materials[rc.material_id].shade(rc);
            }
        }

        return background(ray);
    }

    constexpr Colour background(Ray const& ray) const
    {
        float t = 0.5f * (ray.direction.y() + 1.0f);
        return (1.0f - t) * Colour{1.0f, 1.0f, 1.0f} +
               t * Colour{0.5f, 0.7f, 1.0f};
    }
};
