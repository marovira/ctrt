#pragma once

#include "camera.hpp"
#include "materials.hpp"
#include "ray.hpp"
#include "shapes.hpp"
#include "utils.hpp"
#include "vector.hpp"

class DefaultBackground
{
public:
    constexpr Colour operator()(Ray const&) const
    {
        return Colour{0.0f};
    }
};

class GradientBackground
{
public:
    constexpr Colour operator()(Ray const& ray) const
    {
        float t = 0.5f * (ray.direction.y() + 1.0f);
        return (1.0f - t) * Colour{1.0f, 1.0f, 1.0f} +
               t * Colour{0.5f, 0.7f, 1.0f};
    }
};

template<class ShapeContainer, class BackgroundColour>
class Scene
{
public:
    constexpr Scene(ShapeContainer& container, BackgroundColour bckg) :
        m_shapes{container}, m_background_colour{bckg}
    {}

    constexpr void set_camera(Camera const& camera)
    {
        m_camera = camera;
    }

    constexpr Camera get_camera() const
    {
        return m_camera;
    }

    constexpr ShapeContainer const& get_shapes() const
    {
        return m_shapes;
    }

    constexpr Colour get_background_colour(Ray const& ray) const
    {
        return m_background_colour(ray);
    }

private:
    Camera m_camera;
    ShapeContainer& m_shapes;
    BackgroundColour m_background_colour;
};
