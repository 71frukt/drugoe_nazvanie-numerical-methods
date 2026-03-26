cmake_minimum_required(VERSION 3.21)
project(logarithm_stattest LANGUAGES CXX)

add_executable(${PROJECT_NAME}
    src/main.cpp
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        RLogSU
        dumb_math_common
        tests_common
)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE
        CURRENT_SRC_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}\"
)