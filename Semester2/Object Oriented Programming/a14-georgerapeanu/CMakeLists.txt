cmake_minimum_required(VERSION 3.21)
project(a14_georgerapeanu)

set(CMAKE_CXX_STANDARD  11)


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

include_directories(./include)
include_directories(./include/domain)
include_directories(./include/repository)
include_directories(./include/controller)
include_directories(./include/ui)

add_subdirectory(tests)


find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Core REQUIRED)

add_executable(a14_georgerapeanu
        ./src/domain/Movie.cpp
        ./src/domain/Exceptions.cpp
        src/repository/MemoryRepository.cpp
        ./src/controller/MovieController.cpp
        ./src/ui/UI.cpp
        ./app/main.cpp
        src/repository/FileRepository.cpp
        src/domain/MovieValidator.cpp
        src/repository/CSVWatchlist.cpp
        src/repository/HTMLWatchlist.cpp
        src/repository/MemoryWatchlist.cpp
        src/ui/GUI.cpp
        include/ui/GUI.h
        include/ui/MovieListModel.h
        src/ui/MovieListModel.cpp
        include/ui/AdminGUI.h
        src/ui/AdminGUI.cpp
        src/ui/UserGUI.cpp
        include/ui/UserGUI.h
        include/domain/AbstractMovieAction.h
        src/domain/AbstractMovieAction.cpp
        include/domain/AddMovieAction.h
        include/domain/RemoveMovieAction.h
        include/domain/UpdateMovieAction.h
        src/domain/AddMovieAction.cpp
        src/domain/RemoveMovieAction.cpp
        src/domain/UpdateMovieAction.cpp
        include/repository/UndoActionsStack.h
        src/repository/UndoActionsStack.cpp
        )


target_link_libraries(a14_georgerapeanu Qt5::Widgets Qt5::Core)