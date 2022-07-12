cmake_minimum_required(VERSION 3.21)
project(e916-georgerapeanu-1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

include_directories(
        ./include
        ./include/domain
        ./include/repository
        ./include/controller
        ./include/ui
)

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(e916-georgerapeanu-1 app/main.cpp include/domain/AppException.h src/domain/AppException.cpp include/domain/User.h src/domain/User.cpp include/domain/Question.h src/domain/Question.cpp include/domain/Answer.h src/domain/Answer.cpp include/domain/AbstractObserver.h include/domain/AbstractSubject.h src/domain/AbstractSubject.cpp include/repository/GenericFileRepository.h src/repository/GenericFileRepository.cpp include/controller/Controller.h src/controller/Controller.cpp include/ui/GUIManager.h src/ui/GUIManager.cpp src/ui/UserMainWindow.cpp include/ui/UserMainWindow.h src/ui/UserMainWindow.ui src/ui/SearchWindow.cpp include/ui/SearchWindow.h src/ui/SearchWindow.ui include/ui/MySpinBox.h src/ui/MySpinBox.cpp)
target_link_libraries(e916-georgerapeanu-1
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        )

