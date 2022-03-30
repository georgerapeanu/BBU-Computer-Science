cmake_minimum_required(VERSION 3.21)
project(c__)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_subdirectory(tests)

add_executable(c__
        Graph.cpp UI.cpp)
