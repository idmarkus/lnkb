#pragma once

#include "lnkb/macro/feature.hpp"

#define LNKB_EXPAND(x) x

#if LNKB_FEATURE(if_consteval)
    #define if_consteval if consteval
#else
    #include <type_traits>
    #define if_consteval if (std::is_constant_evaluated())
#endif

#ifndef autoexpr
    #define autoexpr [[maybe_unused]] constexpr static inline auto
    #define lnkbexpr [[maybe_unused]] constexpr static inline
    #define boolexpr [[maybe_unused]] constexpr static inline bool
#else
    #error "lnkb wants to define 'autoexpr', but 'autoexpr' is already defined"
#endif

#ifndef autoeval
    #define autoeval [[maybe_unused]] consteval static inline auto
    #define lnkbeval [[maybe_unused]] consteval static inline
    #define booleval [[maybe_unused]] consteval static inline bool
#else
    #error "lnkb wants to define 'autoeval', but 'autoeval' is already defined"
#endif