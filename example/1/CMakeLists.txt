project(app1 LANGUAGES CXX)

add_executable(${PROJECT_NAME}
    main.cpp
)
target_include_directories(${PROJECT_NAME}
    PRIVATE
    .
)
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    spdlog::spdlog
)
target_compile_options(${PROJECT_NAME}
    PRIVATE
    -std=c++11
    -g
)
