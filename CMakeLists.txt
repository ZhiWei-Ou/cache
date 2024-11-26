cmake_minimum_required(VERSION 3.5.0)

set(VERSION "0.0.1")
set(PROJECT_NAME "cache")

project(${PROJECT_NAME} VERSION ${VERSION} LANGUAGES CXX)

include(FetchContent)

# spdlog
FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG     v1.15.0
)
FetchContent_MakeAvailable(spdlog)

# GTest
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG    v1.15.2
)
FetchContent_MakeAvailable(googletest)


add_library(${PROJECT_NAME} SHARED
    cache.cc
    cache.h
)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

add_subdirectory(example)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

include(CTest)
enable_testing()

add_executable( fixedqueue_test test/fixedqueue_test.cc)
target_link_libraries( fixedqueue_test spdlog::spdlog GTest::gtest_main cache::cache)

add_executable( cache_test test/cache_test.cc)
target_link_libraries( cache_test spdlog::spdlog GTest::gtest_main cache::cache)

include(GoogleTest)
gtest_discover_tests(fixedqueue_test)
gtest_discover_tests(cache_test)
