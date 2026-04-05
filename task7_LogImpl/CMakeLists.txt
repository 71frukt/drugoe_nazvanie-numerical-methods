cmake_minimum_required(VERSION 3.21)
project(log_use LANGUAGES CXX)
enable_testing()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) 

###===========================================FLAGS=================================================

option(SANITIZE "Enable Sanitizers" OFF)

if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_library(project_warnings INTERFACE)
    target_compile_options(project_warnings INTERFACE
        -Wall -Wextra -Werror -Wpedantic
        $<$<CONFIG:DEBUG>:-Og -g>
        $<$<CONFIG:RELEASE>:-O3 -DNDEBUG>
    )
endif()

if(SANITIZE AND NOT MSVC)
    add_library(project_sanitizers INTERFACE)
    target_compile_options(project_sanitizers INTERFACE
        -fsanitize=address,undefined
        -fno-omit-frame-pointer
        -fno-optimize-sibling-calls
    )
    target_link_options(project_sanitizers INTERFACE
        -fsanitize=address,undefined
        -fno-omit-frame-pointer
    )
endif()

###===========================================DEPENDENCIES==========================================

find_package(RLogSU QUIET)

if(NOT RLogSU_FOUND)
    message(STATUS "RLogSU was not found in the system. We use a local copy in lib/RLogSU (or download it if it is not available)...")
    
    include(FetchContent)
    FetchContent_Declare(
        RLogSU
        GIT_REPOSITORY https://github.com/71frukt/RLogSU.git
        GIT_TAG        main
        SOURCE_DIR     ${CMAKE_CURRENT_SOURCE_DIR}/lib/RLogSU
    )

    # add_subdirectory тут автоматически
    FetchContent_MakeAvailable(RLogSU)
else()
    message(STATUS "is found in the system, using the system version.")
endif()

###===========================================SUBDIRECTORY==========================================


# add_subdirectory(tools/cmd_options)
add_subdirectory(source/dumb_math)
add_library(cxxopts INTERFACE)

add_executable(${PROJECT_NAME} source/main.cpp)

###===========================================LIB_LINK==============================================

target_link_libraries(${PROJECT_NAME} PRIVATE project_warnings)

if(SANITIZE AND NOT MSVC)
    target_link_libraries(${PROJECT_NAME} PRIVATE project_sanitizers)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
    RLogSU
    # cmd_options
    dumb_math
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/lib
)