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
    constexpr Colourf trace(Rayf const& ray,
                            ShapeContainer const& shapes,
                            MaterialContainer const& materials) const
    {
        return this->self().trace(ray, shapes, materials);
    }

    constexpr Colourf trace_simple(Rayf const& ray) const
    {
        return this->self().trace_simple(ray);
    }

    constexpr Colourf background(Rayf const& ray) const
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

    constexpr Colourf trace_simple(Rayf const& ray) const
    {
        return background(ray);
    }

    constexpr Colourf background(Rayf const& ray) const
    {
        float t = 0.5f * (ray.direction.y() + 1.0f);
        return (1.0f - t) * Colourf{1.0f, 1.0f, 1.0f} +
               t * Colourf{0.5f, 0.7f, 1.0f};
    }
};

class SphereScene : public Scene<SphereScene>
{
public:
    constexpr SphereScene() = default;

    template<class ShapeContainer, class MaterialContainer>
    constexpr Colourf trace(Rayf const& ray,
                            ShapeContainer const& shapes,
                            MaterialContainer const& materials) const
    {
        if (auto result = shapes.hit(ray); result)
        {
            ShadeRec rc = *result;
            return materials[rc.material_id].shade(rc);
        }

        return background(ray);
    }

    constexpr Colourf background(Rayf const& ray) const
    {
        float t = 0.5f * (ray.direction.y() + 1.0f);
        return (1.0f - t) * Colourf{1.0f, 1.0f, 1.0f} +
               t * Colourf{0.5f, 0.7f, 1.0f};
    }
};
