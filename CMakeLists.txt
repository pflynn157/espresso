cmake_minimum_required(VERSION 3.0.0)
project(espresso)

add_compile_options(-std=c++17 -g)

include_directories(frontend compiler)

add_subdirectory(frontend)
add_subdirectory(compiler)
add_subdirectory(src)

