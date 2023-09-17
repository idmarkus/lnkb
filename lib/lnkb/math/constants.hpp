#pragma once

#include "functions.hpp"
#include "lnkb/macro.h"
#include "lnkb/meta.h"

#include <limits>

#define LNKB_LITERAL_PI 3.14159265358979323846264338327950288419716939937510L
#define LNKB_LITERAL_E  2.71828182845904523536L

namespace lnkb
{
    namespace impl
    {
        template <typename>
        struct expand_float
        {};

        template <meta::Floating T>
        struct expand_float<T>
        {
            // Just to have static member variables instead of calls
            autoexpr epsilon       = std::numeric_limits<T>::epsilon();
            autoexpr round_error   = std::numeric_limits<T>::round_error();
            autoexpr infinity      = std::numeric_limits<T>::infinity();
            autoexpr quiet_NaN     = std::numeric_limits<T>::quiet_NaN();
            autoexpr signaling_NaN = std::numeric_limits<T>::signaling_NaN();
            autoexpr denorm_min    = std::numeric_limits<T>::denorm_min();

            // Taken from cppreference.com TODO: find a better almost_equal()
            autoexpr almost_equal(const T x, const T y, const int ulp)
            {
                // the machine epsilon has to be scaled to the magnitude of the values used
                // and multiplied by the desired precision in ULPs (units in the last place)
                const T diff = math::abs(x - y);
                return diff < std::numeric_limits<T>::min() /* is subnormal */
                       || diff <= epsilon * std::fabs(x + y) * ulp;
            }
        };

        template <meta::Numeric T>
        struct expand_limits : std::numeric_limits<T>, public expand_float<T>
        {
            lnkbexpr T min    = std::numeric_limits<T>::min();
            lnkbexpr T max    = std::numeric_limits<T>::max();
            lnkbexpr T lowest = std::numeric_limits<T>::lowest();

            using std::numeric_limits<T>::is_signed;
            using std::numeric_limits<T>::has_infinity;
            using std::numeric_limits<T>::has_quiet_NaN;
            using std::numeric_limits<T>::has_signaling_NaN;
            using std::numeric_limits<T>::round_style;
            using std::numeric_limits<T>::is_iec559;
            using std::numeric_limits<T>::is_bounded;
            using std::numeric_limits<T>::is_modulo;
            using std::numeric_limits<T>::digits;
            using std::numeric_limits<T>::digits10;
            using std::numeric_limits<T>::max_digits10;
            using std::numeric_limits<T>::radix;
            using std::numeric_limits<T>::min_exponent;
            using std::numeric_limits<T>::min_exponent10;
            using std::numeric_limits<T>::max_exponent;
            using std::numeric_limits<T>::max_exponent10;
            using std::numeric_limits<T>::traps;
            using std::numeric_limits<T>::tinyness_before;
        };
    } // namespace impl

    template <typename>
    struct constants;

    template <meta::Integral T>
    struct constants<T> : public impl::expand_limits<T>
    {};

    template <meta::Floating T>
    struct constants<T> : public impl::expand_limits<T>
    {
        lnkbexpr T PI  = static_cast<T>(LNKB_LITERAL_PI);
        lnkbexpr T TAU = static_cast<T>(2.0L * LNKB_LITERAL_PI);
        lnkbexpr T E   = static_cast<T>(LNKB_LITERAL_E);

        lnkbexpr T HalfPI = static_cast<T>(0.5L * LNKB_LITERAL_PI);
        lnkbexpr T TwoPI  = TAU;
    };

    autoexpr pitest = constants<double>::max;
} // namespace lnkb

#undef LNKB_LITERAL_PI
#undef LNKB_LITERAL_E

// #pragma once
//
// #include "lnkb/meta.hpp"
//
// namespace lnkb::math
//{
// #define LNKB_LITERAL_PI 3.14159265358979323846264338327950288419716939937510L
//     template <meta::Floating T>
//     struct  Constants
//     {
//          static constexpr T pi  = static_cast<T>(LNKB_LITERAL_PI);
//          static constexpr T tau = static_cast<T>(LNKB_LITERAL_PI * 2.0L);
//          static constexpr T e   = static_cast<T>(2.71828182845904523536L);
//          static constexpr T PI  = pi;
//          static constexpr T TAU = tau;
//          static constexpr T E   = e;
//
//          static constexpr T twoPi  = tau;
//          static constexpr T halfPi = static_cast<T>(LNKB_LITERAL_PI * 0.5L);
//     };
// #undef LNKB_LITERAL_PI
//
//     template <meta::Floating T>
//     static constexpr inline T pi = Constants<T>::pi;
//     template <meta::Floating T>
//     static constexpr inline T halfPi = Constants<T>::halfPi;
// } // namespace lnkb::math
