cmake_minimum_required(VERSION 3.20)

project(VISLNKB LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(matplotplusplus
        GIT_REPOSITORY https://github.com/alandefreitas/matplotplusplus
        GIT_TAG origin/master) # or whatever tag you want
FetchContent_GetProperties(matplotplusplus)
if (NOT matplotplusplus_POPULATED)
    FetchContent_Populate(matplotplusplus)
    add_subdirectory(${matplotplusplus_SOURCE_DIR} ${matplotplusplus_BINARY_DIR} EXCLUDE_FROM_ALL)
endif ()

add_executable(VISLNKB main.cpp)

target_link_libraries(VISLNKB PUBLIC matplot PRIVATE lnkb::lnkb)