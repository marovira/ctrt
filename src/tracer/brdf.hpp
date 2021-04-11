#pragma once

#include "shapes.hpp"
#include "utils.hpp"

#include <tuple>
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

    constexpr std::tuple<Colour, Vector> sample_fn(ShadeRec const& sr,
                                                   Vector const& wo) const
    {
        return this->self().sample_fn(sr, wo);
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

    constexpr std::tuple<Colour, Vector> sample_fn(ShadeRec const&,
                                                   Vector const&)
    {
        return {Colour{}, Vector{}};
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

class GlossySpecular : public BRDF<GlossySpecular>
{
public:
    constexpr GlossySpecular()
    {}

    constexpr Colour
    fn(ShadeRec const& rec, Vector const& wo, Vector const& wi) const
    {
        Colour L;
        float n_dot_wi = dot(rec.normal, wi);
        Vector r{-wi + 2.0f * rec.normal * n_dot_wi};
        float r_dot_wo = dot(r, wo);

        if (r_dot_wo > 0.0f)
        {
            L = m_specular_reflection * m_specular_colour *
                utils::pow(r_dot_wo, m_specular_exponent);
        }

        return L;
    }

    constexpr Colour rho(ShadeRec const&, Vector const&) const
    {
        return Colour{};
    }

    constexpr std::tuple<Colour, Vector> sample_fn(ShadeRec const&,
                                                   Vector const&)
    {
        return {Colour{}, Vector{}};
    }

    constexpr void set_specular_reflection(float ks)
    {
        m_specular_reflection = ks;
    }

    constexpr void set_specular_exponent(int exp)
    {
        m_specular_exponent = exp;
    }

    constexpr void set_specular_colour(Colour const& col)
    {
        m_specular_colour = col;
    }

private:
    float m_specular_reflection{0.0f};
    int m_specular_exponent{1};
    Colour m_specular_colour{1.0f};
};

class PerfectSpecular : public BRDF<PerfectSpecular>
{
public:
    constexpr PerfectSpecular()
    {}

    constexpr Colour fn(ShadeRec const&, Vector const&, Vector const&)
    {
        return Colour{};
    }

    constexpr Colour rho(ShadeRec const&, Vector const&)
    {
        return Colour{};
    }

    constexpr std::tuple<Colour, Vector> sample_fn(ShadeRec const& sr,
                                                   Vector const& wo) const
    {
        float n_dot_wo = dot(sr.normal, wo);
        Vector out_vec = -wo + 2.0f * sr.normal * n_dot_wo;
        Colour out_col =
            m_reflection_coeff * m_reflection_colour / dot(sr.normal, out_vec);

        return {out_col, out_vec};
    }

    constexpr void set_reflection_coeff(float kr)
    {
        m_reflection_coeff = kr;
    }

    constexpr void set_reflection_colour(Colour const& col)
    {
        m_reflection_colour = col;
    }

private:
    float m_reflection_coeff{0.0f};
    Colour m_reflection_colour{0.0f};
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

using BRDFs = BRDFWrapper<Lambertian, GlossySpecular, PerfectSpecular>;
