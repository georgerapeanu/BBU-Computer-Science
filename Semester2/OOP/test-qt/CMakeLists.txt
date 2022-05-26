cmake_minimum_required(VERSION 3.21)
project(test_qt)

set(CMAKE_CXX_STANDARD 14)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Core REQUIRED)

add_executable(test_qt
        main.cpp)

target_link_libraries(test_qt Qt5::Widgets Qt5::Core)
