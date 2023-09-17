#pragma once // clang-format off

#include "lnkb/macro/feature.hpp"
#include "lnkb/meta/concepts.hpp"

#include <cstdint>
#include <limits>

namespace lnkb
{
    using f32   [[maybe_unused]] = float;
    using f64   [[maybe_unused]] = double;
    using f80   [[maybe_unused]] = long double;

    using i32   [[maybe_unused]] = std::int_fast32_t;
    using i64   [[maybe_unused]] = std::int_fast64_t;
    using u32   [[maybe_unused]] = std::uint_fast32_t;
    using u64   [[maybe_unused]] = std::uint_fast64_t;

    using i8_t  [[maybe_unused]] = std::int8_t;
    using i16_t [[maybe_unused]] = std::int16_t;
    using i32_t [[maybe_unused]] = std::int32_t;
    using i64_t [[maybe_unused]] = std::int64_t;

    using u8_t  [[maybe_unused]] = std::uint8_t;
    using u16_t [[maybe_unused]] = std::uint16_t;
    using u32_t [[maybe_unused]] = std::uint32_t;
    using u64_t [[maybe_unused]] = std::uint64_t;

    // Literal operator types
    using lit_t  [[maybe_unused]] = long long;
    using ulit_t [[maybe_unused]] = unsigned long long;
    using litf_t [[maybe_unused]] = long double;


    template <meta::Numeric T> using limits = std::numeric_limits<T>;

    #if __has_include(<stdfloat>)
    //  TODO: Leaving this for future reference, as of now (20230915) fixed
    //        width floats only seem to be implemented for float16_t in GCC
    // #include <stdfloat>
    // using f16_t  = std::float16_t;
    // using f32_t  = std::float32_t;
    // using f64_t  = std::float64_t;
    // using bf16_t = std::bfloat16_t;
    #endif
} // namespace lnkb // clang-format on

