set(Protobuf_PREFIX_PATH
    ~/work/opt/bin
    ~/work/opt/lib
    ~/work/opt/include
)
list(APPEND CMAKE_PREFIX_PATH ${Protobuf_PREFIX_PATH})
find_package(Protobuf REQUIRED)

include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS foo.proto)
message("PROTO_SRCS: ${PROTO_SRCS}")
message("PROTO_HDRS: ${PROTO_HDRS}")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/1)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/2)
