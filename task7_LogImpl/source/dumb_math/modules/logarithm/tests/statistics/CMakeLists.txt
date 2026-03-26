cmake_minimum_required(VERSION 3.21)
project(logarithm_stattest LANGUAGES CXX)

add_executable(${PROJECT_NAME} src/main.cpp)

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

set(DATA_DIR "${CMAKE_CURRENT_BINARY_DIR}/data")
set(PLOTS_DIR "${CMAKE_CURRENT_BINARY_DIR}/plots")

file(MAKE_DIRECTORY "${DATA_DIR}")
file(MAKE_DIRECTORY "${PLOTS_DIR}")

set(FILE_1TOINF_DOUBLE  "stat_1toInf_double" )
set(FILE_NEAR1_DOUBLE   "stat_near1_double"  )
set(FILE_1TOINF_FLOAT   "stat_1toInf_float"  )
set(FILE_NEAR1_FLOAT    "stat_near1_float"   )
set(FILE_1TOINF_LDOUBLE "stat_1toInf_ldouble")
set(FILE_NEAR1_LDOUBLE  "stat_near1_ldouble" )

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/config.hpp.in"
    "${CMAKE_CURRENT_BINARY_DIR}/include/statistics/generated/config.hpp"
)
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/include")

set(DATASETS 
    ${FILE_1TOINF_FLOAT} 
    ${FILE_NEAR1_FLOAT}
    ${FILE_1TOINF_DOUBLE} 
    ${FILE_NEAR1_DOUBLE}
    ${FILE_1TOINF_LDOUBLE} 
    ${FILE_NEAR1_LDOUBLE} 
)

set(EXPECTED_TXT_FILES "")
foreach(dataset IN LISTS DATASETS)
    list(APPEND EXPECTED_TXT_FILES "${DATA_DIR}/${dataset}.txt")
endforeach()

add_custom_command(
    OUTPUT ${EXPECTED_TXT_FILES}
    COMMAND $<TARGET_FILE:${PROJECT_NAME}>
    DEPENDS ${PROJECT_NAME}
)

set(ALL_PLOT_FILES "")
foreach(dataset IN LISTS DATASETS)
    set(TXT_FILE "${DATA_DIR}/${dataset}.txt")
    set(PNG_FILE "${PLOTS_DIR}/${dataset}.png")
    
    add_custom_command(
        OUTPUT ${PNG_FILE}
        COMMAND gnuplot -c ${CMAKE_CURRENT_SOURCE_DIR}/src/plot_stat.gp ${TXT_FILE} ${PNG_FILE}
        DEPENDS ${TXT_FILE} ${CMAKE_CURRENT_SOURCE_DIR}/src/plot_stat.gp
    )
    list(APPEND ALL_PLOT_FILES ${PNG_FILE})
endforeach()

add_custom_target(generate_plots DEPENDS ${ALL_PLOT_FILES})