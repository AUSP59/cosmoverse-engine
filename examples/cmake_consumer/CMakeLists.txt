
cmake_minimum_required(VERSION 3.20)
project(consumer_example CXX)
find_package(Cosmoverse REQUIRED)
add_executable(consumer main.cpp)
target_link_libraries(consumer PRIVATE Cosmoverse::cosmoverse)
