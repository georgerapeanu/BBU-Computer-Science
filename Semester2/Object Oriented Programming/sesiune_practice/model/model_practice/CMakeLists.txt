cmake_minimum_required(VERSION 3.21)
project(model)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


include_directories(include/domain)
include_directories(include/repository)
include_directories(include/controller)
include_directories(include/ui)

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(model
        ./app/main.cpp
        include/domain/Exceptions.h
        src/domain/Exceptions.cpp
        include/domain/User.h
        src/domain/User.cpp
        include/domain/Issue.h
        src/domain/Issue.cpp include/repository/GeneralFileRepository.h
        src/repository/GeneralRepository.cpp
        include/controller/IssueController.h
        src/controller/IssueController.cpp
        src/ui/TesterWindow.cpp include/ui/TesterWindow.h src/ui/TesterWindow.ui src/ui/ProgrammerWindow.cpp include/ui/ProgrammerWindow.h include/ui/IssuesModel.h src/ui/IssuesModel.cpp include/ui/MainGUI.h include/controller/UserController.h src/controller/UserController.cpp src/ui/MainGUI.cpp)
target_link_libraries(model
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        )

