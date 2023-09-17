#pragma once

#if __cplusplus < 201100
    #error "C++11 or better is required"
#endif

#ifndef __has_include
    #define __has_include() 0
#endif

#if __has_include(<version>)
    #include <version>
#endif

#define LNKB_FEATURE(x) defined(__cpp_##x)
#define HAS_FEATURE(x)  defined(__cpp_##x)

#define HAS_BITOPS LNKB_FEATURE(lib_bitops)
