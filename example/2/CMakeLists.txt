project(app2 LANGUAGES CXX)

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${CMAKE_CURRENT_SOURCE_DIR}/../foo.proto)

message("--> SRCS: ${PROTO_SRCS}")
message("--> HDRS: ${PROTO_HDRS}")

add_executable(${PROJECT_NAME}
    main.cpp
    ${PROTO_SRCS}
    ${PROTO_HDRS}
)
target_include_directories(${PROJECT_NAME}
    PRIVATE
    .
    ${CMAKE_CURRENT_BINARY_DIR}
)
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    spdlog::spdlog
    protobuf::libprotobuf
)

target_compile_options(${PROJECT_NAME}
    PRIVATE
    -std=c++14
)
