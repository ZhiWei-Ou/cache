cmake_minimum_required(VERSION 3.5.0)

set(VERSION "0.0.1")
set(PROJECT_NAME "cache")

project(${PROJECT_NAME} VERSION ${VERSION} LANGUAGES CXX)

include(FetchContent)

option(BUILD_TEST "Build test" OFF)
option(BUILD_EXAMPLE "Build example" OFF)
option(BUILD_WITH_PROTOBUF "Build with protobuf" OFF)

if (BUILD_WITH_PROTOBUF)
    find_package(Protobuf REQUIRED)
endif()

# spdlog
FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG     v1.15.0
)
FetchContent_MakeAvailable(spdlog)

add_library(${PROJECT_NAME} SHARED
    cache.cc
    cache.h
)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

if (BUILD_EXAMPLE)
    message(STATUS "Build example")
    add_subdirectory(example)
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

include(CTest)
enable_testing()

if (BUILD_TEST)
    message(STATUS "Build test")
    add_subdirectory(test)
endif()
