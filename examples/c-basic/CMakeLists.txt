
cmake_minimum_required(VERSION 3.20)
project(cosmo_example_c C)
find_package(Cosmoverse REQUIRED)
add_executable(c_example main.c)
target_link_libraries(c_example PRIVATE Cosmoverse::cosmoverse)
