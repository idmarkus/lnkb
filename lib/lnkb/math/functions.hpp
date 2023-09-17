/**
 * @lnkb/math/functions.hpp
 * Statically disambiguated compile- and runtime standard functions.
 * GCEM is called at compile-time else STD (will be deprecated in C++26)
 */
#pragma once

#include "lnkb/macro.h"
#include "lnkb/meta.h"

#include <cmath>
#include <gcem.hpp>
#include <type_traits>

namespace gcem
{
    template <lnkb::meta::Floating T1, lnkb::meta::Floating T2, lnkb::meta::Floating T3>
    lnkbexpr lnkb::meta::Common<T1, T2, T3> fma(T1 x, T2 y, T3 z)
    {
        return static_cast<lnkb::meta::Common<T1, T2, T3>>(
            static_cast<long double>(x) * static_cast<long double>(y) + static_cast<long double>(z));
    }
} // namespace gcem
namespace lnkb::math
{

#define LNKB_UNARY2(STD_NAME, GCEM_NAME)                                                                     \
    autoexpr STD_NAME(auto x)                                                                                \
    {                                                                                                        \
        if_consteval { return gcem::GCEM_NAME(x); }                                                          \
        else {                                                                                               \
            return std::STD_NAME(x);                                                                         \
        }                                                                                                    \
    }

#define LNKB_BINARY2(STD_NAME, GCEM_NAME)                                                                    \
    autoexpr STD_NAME(auto x, auto y)                                                                        \
    {                                                                                                        \
        if_consteval { return gcem::GCEM_NAME(x, y); }                                                       \
        else {                                                                                               \
            return std::GCEM_NAME(x, y);                                                                     \
        }                                                                                                    \
    }

#define LNKB_TRINARY2(STD_NAME, GCEM_NAME)                                                                   \
    autoexpr STD_NAME(auto x, auto y, auto z)                                                                \
    {                                                                                                        \
        if_consteval { return gcem::GCEM_NAME(x, y, z); }                                                    \
        else {                                                                                               \
            return std::STD_NAME(x, y, z);                                                                   \
        }                                                                                                    \
    }

#define LNKB_UNARY(STD_NAME)   LNKB_UNARY2(STD_NAME, STD_NAME)
#define LNKB_BINARY(STD_NAME)  LNKB_BINARY2(STD_NAME, STD_NAME)
#define LNKB_TRINARY(STD_NAME) LNKB_TRINARY2(STD_NAME, STD_NAME)

#define LNKB_MATHFN(FN_NAME)                                                                                 \
    [[maybe_unused]] static constexpr inline auto FN_NAME(auto... args)                                      \
    {                                                                                                        \
        if_consteval { return gcem::FN_NAME(args...); }                                                      \
        else {                                                                                               \
            return std::FN_NAME(args...);                                                                    \
        }                                                                                                    \
    }

    // Basic operations
    LNKB_UNARY(abs)
    LNKB_UNARY2(fabs, abs)
    LNKB_UNARY(fmod)
    LNKB_TRINARY(fma)

    // Exponential
    LNKB_UNARY(exp)
    LNKB_UNARY(log)
    LNKB_UNARY(log10)
    LNKB_UNARY(log2)
    LNKB_UNARY(log1p)

    // Power
    LNKB_UNARY(sqrt)
    // LNKB_UNARY(cbrt)
    LNKB_UNARY(hypot)

    // Trigonometry
    LNKB_UNARY(sin)
    LNKB_UNARY(cos)
    LNKB_UNARY(tan)
    LNKB_UNARY(asin)
    LNKB_UNARY(acos)
    LNKB_UNARY(atan)
    LNKB_BINARY(atan2)

    // Hyperbolic
    LNKB_UNARY(sinh)
    LNKB_UNARY(cosh)
    LNKB_UNARY(tanh)
    LNKB_UNARY(asinh)
    LNKB_UNARY(acosh)
    LNKB_UNARY(atanh)

    // Error & gamma
    LNKB_UNARY(erf)
    // LNKB_UNARY(erfc) // 1.0 - std::erf(num)
    LNKB_UNARY(tgamma)
    LNKB_UNARY(lgamma)
    LNKB_BINARY(beta)

    // Rounding
    LNKB_UNARY(ceil)
    LNKB_UNARY(floor)
    LNKB_UNARY(trunc)
    LNKB_UNARY(round)

    // FP-manipulation
    LNKB_BINARY(copysign)
    LNKB_UNARY(signbit)

    // For pow(), we want some special cases.
    namespace impl
    {
        LNKB_MATHFN(pow)

        template <meta::Integral auto i>
        struct [[maybe_unused]] raise
        {
            autoexpr op(auto x)
            {
                auto ret = x;
                for (size_t j = 1; j < i; ++j) ret *= x;
                return ret;
            }
        };

#define DEF_RAISE(P, EXPR)                                                                                   \
    template <>                                                                                              \
    struct [[maybe_unused]] raise<(P)>                                                                       \
    {                                                                                                        \
        static constexpr inline auto op(auto x) { return (EXPR); }                                           \
    };

        DEF_RAISE(2, x * x)
        DEF_RAISE(3, x * x * x)
        DEF_RAISE(4, (x * x) * (x * x))
        DEF_RAISE(5, (x * x) * (x * x) * x)
#undef DEF_RAISE
#undef LNKB_MATHFN
    } // namespace impl

    template <meta::Integral auto i>
    [[maybe_unused]] autoexpr raise(auto x)
    {
        return impl::raise<i>::op(x);
    }

    autoexpr pow(auto x, meta::Integral auto y) { return raise<y>(x); }
    autoexpr pow(auto x, meta::Floating auto y) { return impl::pow(x, y); }

    template <meta::Integral Z, meta::Floating R>
    lnkbexpr R pow(Z x, R y)
    {
        return impl::pow(static_cast<R>(x), y);
    }

    autoexpr pow2(auto y) { return pow(static_cast<decltype(y)>(2), y); }

    autoexpr square(auto x) { return raise<2>(x); }
    autoexpr cube(auto x) { return raise<3>(x); }
} // namespace lnkb::math
