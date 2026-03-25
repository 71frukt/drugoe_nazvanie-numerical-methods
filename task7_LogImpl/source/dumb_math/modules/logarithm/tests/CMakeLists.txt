cmake_minimum_required(VERSION 3.21)
project(logarithm_tests LANGUAGES CXX)

enable_testing() 

find_package(GTest REQUIRED)

find_library(GMP_LIB  gmp  REQUIRED)
find_library(MPFR_LIB mpfr REQUIRED)

add_executable(logarithm_tests
    src/calc_ulp_error.cpp
    src/test_ulp_error.cpp
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lib>
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        logarithm

        ${GMP_LIB}
        ${MPFR_LIB}

        GTest::gtest_main
        GTest::gtest 
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})