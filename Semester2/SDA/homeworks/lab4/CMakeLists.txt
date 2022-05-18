cmake_minimum_required(VERSION 3.21)
project(lab4)

set(CMAKE_CXX_STANDARD 14)

include_directories(Bag)

add_executable(lab4
        Bag/App.cpp
        Bag/Bag.cpp
        Bag/Bag.h
        Bag/BagIterator.cpp
        Bag/BagIterator.h
        Bag/ExtendedTest.cpp
        Bag/ExtendedTest.h
        Bag/ShortTest.cpp
        Bag/ShortTest.h)
