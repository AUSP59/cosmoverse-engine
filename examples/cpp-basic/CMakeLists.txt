
cmake_minimum_required(VERSION 3.20)
project(cosmo_example_cpp CXX)
find_package(Cosmoverse REQUIRED)
add_executable(cpp_example main.cpp)
target_link_libraries(cpp_example PRIVATE Cosmoverse::cosmoverse)
