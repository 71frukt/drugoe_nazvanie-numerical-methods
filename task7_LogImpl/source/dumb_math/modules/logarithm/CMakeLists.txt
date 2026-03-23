cmake_minimum_required(VERSION 3.21)
project(logarithm LANGUAGES CXX)

add_library(${PROJECT_NAME} INTERFACE 
    include/logarithm/logarithm.hpp
)

target_link_libraries(${PROJECT_NAME} INTERFACE
    RLogSU
)

target_include_directories(${PROJECT_NAME} INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
