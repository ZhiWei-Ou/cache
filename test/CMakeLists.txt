
# GTest
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG    v1.15.2
)
FetchContent_MakeAvailable(googletest)

# GBenchmark
FetchContent_Declare(
    gbenchmark
    GIT_REPOSITORY https://github.com/google/benchmark.git
    GIT_TAG    v1.9.1
)
FetchContent_MakeAvailable(gbenchmark)

add_executable( fixedqueue_test fixedqueue_test.cc)
target_link_libraries( fixedqueue_test spdlog::spdlog GTest::gtest_main cache::cache)

if (BUILD_WITH_PROTOBUF)
    protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${CMAKE_CURRENT_SOURCE_DIR}/foo.proto)

    add_executable( cache_test cache_test.cc ${PROTO_SRCS} ${PROTO_HDRS})
    target_include_directories( cache_test PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
    target_link_libraries( cache_test PRIVATE GTest::gtest_main cache::cache ${Protobuf_LIBRARIES})
    target_compile_options( cache_test PRIVATE --std=c++14)
    target_compile_definitions( cache_test PRIVATE WITH_PROTOBUF)
else()
    add_executable( cache_test cache_test.cc)
    target_link_libraries( cache_test GTest::gtest_main cache::cache)
    target_link_libraries( cache_test GTest::gtest_main cache::cache)
    target_compile_options( cache_test PRIVATE --std=c++14)
endif()

include(GoogleTest)
gtest_discover_tests(fixedqueue_test)
gtest_discover_tests(cache_test)

# benchmark
add_executable( cache_benchmark cache_benchmark.cc)
target_link_libraries( cache_benchmark cache::cache benchmark::benchmark_main)
target_compile_options( cache_benchmark PRIVATE --std=c++14)
