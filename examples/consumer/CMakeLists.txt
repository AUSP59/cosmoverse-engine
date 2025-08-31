
cmake_minimum_required(VERSION 3.16)
project(cosmoverse_consumer CXX)
set(CMAKE_CXX_STANDARD 20)
# Try config package first
find_package(cosmoverse QUIET CONFIG)
if (cosmoverse_FOUND)
  add_executable(consumer main.cpp)
  target_link_libraries(consumer PRIVATE cosmoverse)
else()
  message(WARNING "cosmoverse package not found; building standalone consumer")
  add_executable(consumer main.cpp)
endif()
