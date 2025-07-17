cmake_minimum_required(VERSION 3.10)
project(Sniffer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build Google Test unit tests" ON)

add_subdirectory(src)
if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()
