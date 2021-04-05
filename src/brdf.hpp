#pragma once

#include "shapes.hpp"
#include "utils.hpp"

#include <variant>
#include <zeus/constants.hpp>

template<typename T>
class BRDF : public utils::StaticBase<T, BRDF>
{
public:
    constexpr BRDF()
    {}

    constexpr Colour fn(ShadeRec const& rec,
                        Vector const& reflected,
                        Vector const& incoming) const
    {
        return this->self().fn(rec, reflected, incoming);
    }

    constexpr Colour rho(ShadeRec const& rec, Vector const& reflected) const
    {
        return this->self().rho(rec, reflected);
    }
};

class Lambertian : public BRDF<Lambertian>
{
public:
    constexpr Lambertian()
    {}

    constexpr Colour fn(ShadeRec const&, Vector const&, Vector const&) const
    {
        return m_diffuse_colour * m_diffuse_reflection *
               zeus::Constants<float>::one_by_pi;
    }

    constexpr Colour rho(ShadeRec const&, Vector const&) const
    {
        return m_diffuse_colour * m_diffuse_reflection;
    }

    constexpr void set_diffuse_reflection(float refl)
    {
        m_diffuse_reflection = refl;
    }

    constexpr void set_diffuse_colour(Colour const& colour)
    {
        m_diffuse_colour = colour;
    }

private:
    Colour m_diffuse_colour;
    float m_diffuse_reflection{0.0f};
};

template<class... BRDFs>
class BRDFWrapper
{
public:
    template<typename T, typename = utils::Contains<T, BRDFs...>>
    constexpr BRDFWrapper(T&& elem) : m_brdf{elem}
    {}

    constexpr Colour fn(ShadeRec const& rec,
                        Vector const& reflected,
                        Vector const& incoming) const
    {
        return std::visit(
            [rec, reflected, incoming](auto const& elem) {
                return elem.fn(rec, reflected, incoming);
            },
            m_brdf);
    }

    constexpr Colour rho(ShadeRec const& rec, Vector const& reflected) const
    {
        return std::visit([rec, reflected](auto const& elem) {
            return elem.rho(rec, reflected);
        });
    }

private:
    std::variant<BRDFs...> m_brdf;
};

using BRDFs = BRDFWrapper<Lambertian>;
