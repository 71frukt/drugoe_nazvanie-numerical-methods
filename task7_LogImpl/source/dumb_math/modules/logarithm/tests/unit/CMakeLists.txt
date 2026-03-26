cmake_minimum_required(VERSION 3.21)
project(logarithm_unittests LANGUAGES CXX)

enable_testing() 

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

target_link_libraries(logarithm_unittests
    PRIVATE
        GTest::gtest_main
        tests_common
)

find_library(GMP_LIB  gmp  REQUIRED)
find_library(MPFR_LIB mpfr REQUIRED)

add_executable(${PROJECT_NAME}
    src/test_ulp_error.cpp
)


target_link_libraries(${PROJECT_NAME}
    PRIVATE
        dumb_math_common
        dumb_math_internal
        
        tests_common

        logarithm

        ${GMP_LIB}
        ${MPFR_LIB}

        GTest::gtest_main
        GTest::gtest
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})