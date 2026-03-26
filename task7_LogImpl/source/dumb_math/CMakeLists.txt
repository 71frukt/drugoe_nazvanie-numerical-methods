cmake_minimum_required(VERSION 3.15)
project(dumb_math LANGUAGES CXX)

#================== public ===============================
add_library(dumb_math_common INTERFACE)
target_include_directories(dumb_math_common INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

#================= private ===============================
add_library(dumb_math_internal INTERFACE)
target_include_directories(dumb_math_internal INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lib>
)

add_subdirectory(modules/logarithm)

add_library(${PROJECT_NAME} INTERFACE)

target_link_libraries(${PROJECT_NAME} INTERFACE
    dumb_math_common
    logarithm    
)