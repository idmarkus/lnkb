#pragma once

#include "lnkb/macro.h"
#include "lnkb/math/constants.hpp"
#include "lnkb/math/functions.hpp"
#include "lnkb/math/numerics.hpp"
#include "lnkb/meta.h"

#define DEF_EASING(IN_EXPR, OUT_EXPR, COMP_IN_EXPR, COMP_OUT_EXPR)                                           \
    template <meta::Floating T>                                                                              \
    static constexpr inline T in(const T t)                                                                  \
    {                                                                                                        \
        return (IN_EXPR);                                                                                    \
    }                                                                                                        \
    template <meta::Floating T>                                                                              \
    static constexpr inline T out(const T t)                                                                 \
    {                                                                                                        \
        return (OUT_EXPR);                                                                                   \
    }                                                                                                        \
    template <meta::Floating T>                                                                              \
    static constexpr inline T comp_in(const T t)                                                             \
    {                                                                                                        \
        return (COMP_IN_EXPR);                                                                               \
    }                                                                                                        \
    template <meta::Floating T>                                                                              \
    static constexpr inline T comp_out(const T t)                                                            \
    {                                                                                                        \
        return (COMP_OUT_EXPR);                                                                              \
    }                                                                                                        \
    template <meta::Floating T>                                                                              \
    static constexpr inline T inout(const T t)                                                               \
    {                                                                                                        \
        return (t < static_cast<decltype(t)>(0.5)) ? comp_in(t) : comp_out(t);                               \
    }                                                                                                        \
    template <meta::Floating T>                                                                              \
    static constexpr inline T operator()(const T t)                                                          \
    {                                                                                                        \
        return inout(t);                                                                                     \
    }

namespace lnkb::meta // clang-format off
{
    template <class C> concept Easing =
        requires(f32 t32, f64 t64, f80 t80) {
        { C::in(t32)        } -> meta::Same<f32>;
        { C::out(t32)       } -> meta::Same<f32>;
        { C::comp_in(t32)   } -> meta::Same<f32>;
        { C::comp_out(t32)  } -> meta::Same<f32>;
        { C::inout(t32)     } -> meta::Same<f32>;

        { C::in(t64)        } -> meta::Same<f64>;
        { C::out(t64)       } -> meta::Same<f64>;
        { C::comp_in(t64)   } -> meta::Same<f64>;
        { C::comp_out(t64)  } -> meta::Same<f64>;
        { C::inout(t64)     } -> meta::Same<f64>;

        { C::in(t80)       } -> meta::Same<f80>;
        { C::out(t80)      } -> meta::Same<f80>;
        { C::comp_in(t80)  } -> meta::Same<f80>;
        { C::comp_out(t80) } -> meta::Same<f80>;
        { C::inout(t80)    } -> meta::Same<f80>;
    }; // clang-format on
} // namespace lnkb::meta

namespace lnkb::ease
{
    /**
     * General polynomial easing, quadratic = raise\<2>, cubic = raise\<3>, etc.
     */
    template <meta::Integral auto i>
    struct polynomial
    {
        DEF_EASING(math::raise<i>(t),                           // in
                   math::raise<i>(t - 1.0),                     // out
                   math::raise<i - 1>(2.0) * math::raise<i>(t), // inout in
                   0.5 * math::raise<i>((2.0 * t) - 2.0) + 1.0  // inout out
        )
    };

    /**
     * The formula for out() in composition is different for even and odd i's, hence two specializations.
     */
    template <meta::Integral auto i>
        requires(i % 2 == 0)
    struct polynomial<i>
    {
        DEF_EASING(math::raise<i>(t),                                       // in
                   math::raise<i>(t - 1.0),                                 // out
                   math::raise<i - 1>(2.0) * math::raise<i>(t),             // inout in
                   -math::raise<i - 1>(2.0) * math::raise<i>(t - 1.0) + 1.0 // inout out
        )
    };

    /**
     * Named polynomial typedef
     */
    template <meta::Integral auto i>
    using raise = polynomial<i>;

    using linear    = polynomial<1>;
    using quadratic = polynomial<2>;
    using cubic     = polynomial<3>;
    using quartic   = polynomial<4>;
    using quintic   = polynomial<5>;
    using sextic    = polynomial<6>;
    //    [[maybe_unused]] static constexpr auto hexic = sextic {};
    using hexic     = sextic;
    using septic    = polynomial<7>;
    using heptic    = septic;
    using octic     = polynomial<8>;
    using nonic     = polynomial<9>;
    using decic     = polynomial<10>;

    static_assert(meta::Easing<decic>);

    struct sinusoidal
    {
        DEF_EASING(math::sin((t - T(1)) * constants<T>::HalfPI) + 1, math::sin(t * constants<T>::HalfPI),
                   0.5 * (1.0 - math::cos(t * constants<T>::PI)),
                   0.5 * (1.0 - math::cos(t * constants<T>::PI)))
    };

    using sine = sinusoidal;

    struct circular
    {
        // y = (1/2)(1 - sqrt(1 - 4x^2))           ; [0, 0.5)
        // y = (1/2)(sqrt(-(2x - 3)*(2x - 1)) + 1) ; [0.5, 1]
        DEF_EASING(1.0 - math::sqrt(1.0 - math::square(t)), math::sqrt((2.0 - t) * t),
                   0.5 * (1.0 - math::sqrt(1.0 - 4.0 * math::square(t))),
                   0.5 * (math::sqrt(-(2.0 * t) - 3.0) * ((2.0 * t) - 1.0)) + 1.0)
    };

    struct exponential
    {
        // y = (1/2)2^(10(2x - 1))         ; [0,0.5)
        // y = -(1/2)*2^(-10(2x - 1))) + 1 ; [0.5,1]
        DEF_EASING((t == 0.0) ? t : math::pow(2, 10 * (t - 1)), (t == 1.0) ? t : 1.0 - math::pow(2, -10 * t),
                   (t == 0.0) ? t : 0.5 * math::pow(2, (20 * t) - 10),
                   (t == 1.0) ? t : -0.5 * math::pow(2, (-20 * t) + 10) + 1)
    };

    struct elastic
    {
        // y = (1/2)*sin(13pi/2*(2*x))*pow(2, 10 * ((2*x) - 1))      ; [0,0.5)
        // y = (1/2)*(sin(-13pi/2*((2x-1)+1))*pow(2,-10(2*x-1)) + 2) ; [0.5,1]
        DEF_EASING(math::sin(13.0 * constants<T>::HalfPI * t) * math::pow2(10.0 * (t - 1.0)),
                   math::sin(-13.0 * constants<T>::HalfPI * (t + 1.0)) * math::pow2(-10.0 * t),
                   0.5 * math::sin(13 * constants<T>::HalfPI * (2 * t)) * math::pow2(10 * ((2 * t) - 1)),
                   0.5
                       * (math::sin(-13 * constants<T>::HalfPI * ((2 * t - 1) + 1))
                              * math::pow2(-10 * (2 * t - 1))
                          + 2))
    };
} // namespace lnkb::ease
