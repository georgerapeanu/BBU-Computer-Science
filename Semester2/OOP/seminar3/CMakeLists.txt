cmake_minimum_required(VERSION 3.21)
project(seminar3)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(seminar3
        DynamicVector.h
        main.cpp
        Tests.cpp
        Tests.h)
