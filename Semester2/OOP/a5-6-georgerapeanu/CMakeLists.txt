cmake_minimum_required(VERSION 3.21)
project(a5_6_georgerapeanu)

set(CMAKE_CXX_STANDARD  11)

include_directories(./include)
include_directories(./include/domain)
include_directories(./include/repository)
include_directories(./include/controller)
include_directories(./include/ui)

add_subdirectory(tests)


add_executable(a5_6_georgerapeanu
        ./src/domain/DynamicVector.cpp
        ./src/domain/Movie.cpp
        ./src/domain/Exceptions.cpp
        ./src/repository/Repository.cpp
        ./src/controller/MovieController.cpp
        ./src/ui/UI.cpp
        ./app/main.cpp)

