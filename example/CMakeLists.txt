add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/1)

if (BUILD_WITH_PROTOBUF)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/2)
endif()
