cmake_minimum_required(VERSION 3.15)
project(task5_chi_generator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Включение генерации compile_commands.json для clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(source/rnd_bit_generators)
add_subdirectory(source/rnd_normal_generator)
add_subdirectory(source/chi_sq_generator)
add_subdirectory(lib/RLogSU)

add_executable(${PROJECT_NAME}
    source/main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    RLogSU
    rnd_bit_generators
    chi_sq_generator
)

target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -O2
)

#================= Additional task =====================================
add_subdirectory(source/bivariate_normal_generator)

add_executable(additional_task
    source/additional_task.cpp
)

target_link_libraries(additional_task PRIVATE
    RLogSU
    rnd_bit_generators
    chi_sq_generator
    bivariate_normal_generator
)

target_compile_options(additional_task PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -O2
)