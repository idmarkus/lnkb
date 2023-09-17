cmake_minimum_required(VERSION 3.20)

project(lnkb
        VERSION 0.1
        LANGUAGES CXX)


option(LNKB_MAKE_VIS "Make visualizations of math functions" OFF)

if (LNKB_MAKE_VIS)
    add_subdirectory(vis)

endif ()

add_subdirectory(lib)