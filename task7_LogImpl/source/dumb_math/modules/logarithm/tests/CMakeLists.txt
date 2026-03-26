cmake_minimum_required(VERSION 3.21)
project(logarithm_tests LANGUAGES CXX)

#=================== tests_common ========================
add_library(tests_common INTERFACE)

find_library(GMP_LIB NAMES gmp
    PATHS /usr/lib/x86_64-linux-gnu /usr/local/lib /usr/lib
    REQUIRED
)

find_library(MPFR_LIB NAMES mpfr
    PATHS /usr/lib/x86_64-linux-gnu /usr/local/lib /usr/lib
    REQUIRED
)

find_path(MPFR_INCLUDE_DIR NAMES mpfr.h
    PATHS /usr/include /usr/local/include
    REQUIRED
)

target_include_directories(tests_common INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}/common
    ${MPFR_INCLUDE_DIR}
)

target_link_libraries(tests_common
    INTERFACE
        dumb_math_internal
        logarithm
        ${GMP_LIB}
        ${MPFR_LIB}
)
#=========================================================


add_subdirectory(unit)
add_subdirectory(statistics)