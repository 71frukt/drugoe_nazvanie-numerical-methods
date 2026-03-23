cmake_minimum_required(VERSION 3.21)
project(lookup_table_builder LANGUAGES CXX)

add_executable(${PROJECT_NAME}
    src/lookup_table_builder.cpp

    tools/cmd_options/cmd_options.cpp
)

target_include_directories(${PROJECT_NAME} INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/tools
        ${CMAKE_SOURCE_DIR}/lib
)