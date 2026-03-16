cmake_minimum_required(VERSION 3.15)
project(rnd_generators_test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Включение генерации compile_commands.json для clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(source/first_level_tests)
add_subdirectory(source/two_level_test)
add_subdirectory(source/uniformity_tests)
add_subdirectory(source/utils)
add_subdirectory(lib/RLogSU)

add_executable(${PROJECT_NAME}
    source/main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    RLogSU
    first_level_tests
    two_level_test
)

target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -O2
)