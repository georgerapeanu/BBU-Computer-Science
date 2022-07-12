cmake_minimum_required(VERSION 3.21)
project(t3_georgerapeanu)

set(CMAKE_CXX_STANDARD  11)


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

include_directories(./domain)
include_directories(./repository)
include_directories(./controller)
include_directories(./ui)


find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Core REQUIRED)

add_executable(t3_georgerapeanu
        main.cpp
        ./domain/Document.cpp
        ./domain/Document.h
        ./domain/Exceptions.cpp
        ./domain/Exceptions.h
        ./repository/FileRepository.cpp
        ./repository/FileRepository.h controller/Controller.cpp controller/Controller.h ui/GUI.cpp ui/GUI.h)

target_link_libraries(t3_georgerapeanu Qt5::Widgets Qt5::Core)

