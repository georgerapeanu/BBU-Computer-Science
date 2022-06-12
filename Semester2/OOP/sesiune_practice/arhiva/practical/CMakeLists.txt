cmake_minimum_required(VERSION 3.21)
project(practical)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

include_directories(include
                src
                include/domain
                include/repository
                include/controller
                include/ui
                src/domain
                src/repository
                src/controller
                src/ui)


find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(practical
        app/main.cpp
        include/domain/AppException.h
        src/domain/AppException.cpp
        include/domain/User.h
        src/domain/User.cpp
        include/domain/Question.h
        src/domain/Question.cpp
        include/domain/Answer.h
        src/domain/Answer.cpp
        include/repository/FileRepository.h
        src/repository/FileRepository.cpp
        include/controller/Controller.h
        include/domain/AbstractObserver.h
        include/domain/AbstractSubject.h
        src/domain/AbstractSubject.cpp
        src/controller/Controller.cpp src/ui/UserMainWindow.cpp include/ui/UserMainWindow.h src/ui/UserMainWindow.ui src/ui/UserSearchWindow.cpp include/ui/UserSearchWindow.h src/ui/UserSearchWindow.ui include/ui/GUIManager.h src/ui/GUIManager.cpp include/ui/CustomSpinWidget.h src/ui/CustomSpinWidget.cpp)
target_link_libraries(practical
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        )

