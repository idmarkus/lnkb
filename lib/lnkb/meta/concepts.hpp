#pragma once

#include <concepts>
#include <type_traits>

namespace lnkb::meta
{
    template <typename T> concept Floating   = std::floating_point<T>;
    template <typename T> concept Integral   = std::integral<T>;
    template <typename T> concept Unsigned   = std::unsigned_integral<T>;
    template <typename T> concept Arithmetic = std::is_arithmetic_v<T>;
    template <typename T> concept Numeric    = Arithmetic<T>;

    template <typename T> concept NonFloating   = !Floating<T>;
    template <typename T> concept NonIntegral   = !Integral<T>;
    template <typename T> concept NonArithmetic = !Arithmetic<T>;
    template <typename T> concept NonNumeric    = !Numeric<T>;

    template <class C>
    concept Indexable = requires(C & c, std::size_t i) {
        c[i];
        {
            c.size()
        } -> std::convertible_to<std::size_t>;
    };

    template <class C> concept NonIndexable = !Indexable<C>;

    template <class C>
    concept Indexable2D = requires(C & c, std::size_t i) {
        {
            c[i]
        } -> NonIndexable;
        {
            c.size()
        } -> std::convertible_to<std::size_t>;
    };
} // namespace lnkb::meta
