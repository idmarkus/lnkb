#pragma once

#include "lnkb/macro.h"
#include "lnkb/meta.h"

// For now, we only support C++20 + so we can assume <bit> is available
// otherwise we could feature test here, and use intrinsics or software
// #if HAS_FEATURE(lib_bitops)

#include <bit>

namespace lnkb::bit
{
    template <meta::Unsigned T>
    lnkbexpr T single_bit(const T x)
    {
        return std::has_single_bit(x);
    }

    autoexpr width(meta::Unsigned auto x) { return std::bit_width(x); }

    autoexpr popcnt(meta::Unsigned auto x) { return std::popcount(x); }

    autoexpr clz(meta::Unsigned auto x) { return std::countl_zero(x); }
    autoexpr ctz(meta::Unsigned auto x) { return std::countr_zero(x); }

    autoexpr lzcnt(meta::Unsigned auto x) { return clz(x); }
    autoexpr tzcnt(meta::Unsigned auto x) { return ctz(x); }

    autoexpr rotl(meta::Unsigned auto x, int steps) { return std::rotl(x, steps); }
    autoexpr rotr(meta::Unsigned auto x, int steps) { return std::rotr(x, steps); }

    autoexpr ceil(meta::Unsigned auto x) { return std::bit_ceil(x); }
    autoexpr floor(meta::Unsigned auto x) { return std::bit_floor(x); }

    /**
     * <> Reinterpret cast
     */
    template <meta::Numeric T>
    lnkbexpr T cast(const auto x)
    {
        return std::bit_cast<T>(x);
    }

    template <meta::Numeric T>
    lnkbexpr T reinterpret(const auto x)
    {
        return std::bit_cast<T>(x);
    }

    namespace endian
    {
        autoexpr little = std::endian::native == std::endian::little;
        autoexpr big    = std::endian::native == std::endian::big;
        autoexpr mixed  = !(little || big);
    } // namespace endian

    /**
     * <> bit::shl <>
     * (Costless) endian agnostic shift towards msb.
     * @result x \<\< y on little (x86) else x >> y
     */
    autoexpr shl(meta::Unsigned auto x, meta::Integral auto i)
    {
        static_assert(!endian::mixed, "lnkb::bit does not support mixed endian systems");
        if constexpr (endian::little) return x << i;
        else
            return x >> i;
    }

    /**
     * <> bit::shr <>
     * (Costless) endian agnostic shift towards lsb.
     * @result x >> y on little (x86) else x \<\< y
     */
    autoexpr shr(meta::Unsigned auto x, meta::Integral auto i)
    {
        static_assert(!endian::mixed, "lnkb::bit does not support mixed endian systems");
        if constexpr (endian::little) return x >> i;
        else
            return x << i;
    }
} // namespace lnkb::bit