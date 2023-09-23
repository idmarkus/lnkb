cmake_minimum_required(VERSION 3.14)

include(FetchContent)
FetchContent_Declare(
        gcem
        GIT_REPOSITORY https://github.com/kthohr/gcem.git
        GIT_TAG        v1.17.0
)
FetchContent_MakeAvailable(gcem)