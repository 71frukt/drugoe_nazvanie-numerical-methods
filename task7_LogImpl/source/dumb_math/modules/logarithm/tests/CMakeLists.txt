cmake_minimum_required(VERSION 3.21)
project(logarithm_tests LANGUAGES CXX)

#=================== tests_common ========================
add_library(tests_common INTERFACE)

find_package(PkgConfig REQUIRED)

pkg_check_modules(MPFR REQUIRED IMPORTED_TARGET mpfr)
pkg_check_modules(GMP  REQUIRED IMPORTED_TARGET gmp)

target_include_directories(tests_common INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}/common
)

target_link_libraries(tests_common
    INTERFACE
        dumb_math_internal
        logarithm
        
        PkgConfig::MPFR
        PkgConfig::GMP
)
#=========================================================


add_subdirectory(unit)
add_subdirectory(statistics)