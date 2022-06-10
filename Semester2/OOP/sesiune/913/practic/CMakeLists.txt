cmake_minimum_required(VERSION 3.21)
project(practic)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


include_directories(include)
include_directories(include/domain)
include_directories(include/repository)
include_directories(include/controller)
include_directories(include/ui)

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUITED)

add_executable(practic
        app/main.cpp src/domain/Question.cpp include/domain/Participant.h src/domain/Participant.cpp include/repository/GenericFileRepository.h src/repository/GenericFileRepository.cpp include/domain/AppException.h src/domain/AppException.cpp include/controller/Controller.h src/controller/Controller.cpp src/ui/ParticipantWindow.cpp include/ui/ParticipantWindow.h src/ui/ParticipantWindow.ui include/domain/AbstractObserver.h include/domain/AbstractSubject.h src/domain/AbstractSubject.cpp src/ui/PresenterWindow.cpp include/ui/PresenterWindow.h src/ui/PresenterWindow.ui include/ui/GUIManager.h src/ui/GUIManager.cpp)
target_link_libraries(practic Qt5::Core Qt5::Gui Qt5::Widgets)
