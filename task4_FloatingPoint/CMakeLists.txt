cmake_minimum_required(VERSION 3.15)
project(task4_FloatingPoint LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Включение генерации compile_commands.json для clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(source/cmd_options)

add_executable(${PROJECT_NAME}
    source/main.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    cmd_options
)

target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -O2
)