cmake_minimum_required(VERSION 3.20)

project(LIBLNKB
        VERSION 0.1
        LANGUAGES CXX)

include (FetchGCEM)

file(GLOB_RECURSE HEADER_LIST CONFIGURE_DEPENDS "${LIBLNKB_SOURCE_DIR}/lnkb/*.h*")
file(GLOB_RECURSE SOURCE_LIST CONFIGURE_DEPENDS "${LIBLNKB_SOURCE_DIR}/lnkb/*.c*")

add_library(LIBLNKB INTERFACE lnkb.h ${SOURCE_LIST} ${HEADER_LIST})

target_include_directories(LIBLNKB INTERFACE "${LIBLINKB_SOURCE_DIR}")

set_target_properties (
        LIBLNKB
        PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
        USE_FOLDERS ON
)
#set_target_properties(LIBLNKB PROPERTIES )
#set_target_properties(LIBLNKB PROPERTIES )
#set_target_properties(LIBLNKB PROPERTIES )

## Check compiler support for C++23
#if (MSVC)
#
#else ()
#    include(CheckCXXCompilerFlag)
#    CHECK_CXX_COMPILER_FLAG("-std=c++23" SUPPORTS_CXX23)
#    CHECK_CXX_COMPILER_FLAG("-std=c++2b" SUPPORTS_CXX2b)
#endif ()
#
#if (SUPPORTS_CXX23 OR SUPPORTS_CXX2b)
#    set_target_properties(
#            LIBLNKB
#            PROPERTIES
#            CXX_STANDARD 23
#            CXX_STANDARD_REQUIRED ON
#            CXX_EXTENSIONS OFF
#    )
#endif ()



target_link_libraries(
        LIBLNKB
        INTERFACE
        gcem
)

add_library(lnkb::lnkb ALIAS LIBLNKB)