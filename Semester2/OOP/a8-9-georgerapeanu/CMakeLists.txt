cmake_minimum_required(VERSION 3.21)
project(a8_9_georgerapeanu)

set(CMAKE_CXX_STANDARD  11)

include_directories(./include)
include_directories(./include/domain)
include_directories(./include/repository)
include_directories(./include/controller)
include_directories(./include/ui)

add_subdirectory(tests)


add_executable(a8_9_georgerapeanu
        ./src/domain/Movie.cpp
        ./src/domain/Exceptions.cpp
        src/repository/MemoryRepository.cpp
        ./src/controller/MovieController.cpp
        ./src/ui/UI.cpp
        ./app/main.cpp
        src/repository/FileRepository.cpp
        src/domain/MovieValidator.cpp src/repository/CSVWatchlist.cpp src/repository/HTMLWatchlist.cpp src/repository/MemoryWatchlist.cpp)

