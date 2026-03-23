cmake_minimum_required(VERSION 3.15)
project(dumb_math LANGUAGES CXX)

add_subdirectory(modules/logarithm)
add_subdirectory(tools/lookup_table_builder)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(dumb_math INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(${PROJECT_NAME} INTERFACE
    logarithm    
)