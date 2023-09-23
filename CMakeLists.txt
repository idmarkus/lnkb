cmake_minimum_required(VERSION 3.20)

project(devlnkb LANGUAGES CXX)

list (APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

option(LNKB_MAKE_VIS "Make visualizations of math functions" OFF)
mark_as_advanced(LNKB_MAKE_VIS)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
    set(CMAKE_CXX_STANDARD 23)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)
    add_executable(devlnkb main.cpp)
endif ()

if (LNKB_MAKE_VIS)
    add_subdirectory(vis)
endif ()

add_subdirectory(lib)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    target_link_libraries(devlnkb PRIVATE lnkb::lnkb)
endif ()