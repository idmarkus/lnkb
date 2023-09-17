#pragma once

#include <type_traits>

namespace lnkb::meta
{
    template <typename A, typename B> concept Same = std::is_same_v<A, B>;

    template <typename... Ts>
    using Common = std::common_type_t<Ts...>;
} // namespace lnkb::meta

  // clang-format off
namespace lnkb::meta
{
    // Canonical
    struct Integer {};
    struct Natural {};
    struct Real {};

    using Signed = Integer;
    using Float  = Real;

    template <class C> concept Canonical = Same<C, Integer> || Same<C, Natural> || Same<C, Real>;
} // namespace meta
// clang-format on