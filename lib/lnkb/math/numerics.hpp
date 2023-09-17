#pragma once

#include "lnkb/bit.h"
#include "lnkb/bit/intrinsics.hpp"
#include "lnkb/macro.h"
#include "lnkb/meta.h"

namespace lnkb::math
{
    boolexpr even(meta::Integral auto x) { return (x % 2 == 0); }
    boolexpr even(f32 x) { return static_cast<u32_t>(x) % 2 == 0; }
    boolexpr even(f64 x) { return static_cast<u64_t>(x) % 2 == 0; }
    boolexpr even(f80 x) { return static_cast<uintmax_t>(x) % 2 == 0; }

    boolexpr is_pow2(meta::Unsigned auto x) { return bit::single_bit(x); }
    autoexpr next_pow2(meta::Unsigned auto x) { return bit::ceil(bit::shl(x)); }
    autoexpr prev_pow2(meta::Unsigned auto x) { return bit::floor(bit::shr(x)); }
} // namespace lnkb::math
