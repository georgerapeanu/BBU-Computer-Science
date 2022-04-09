cmake_minimum_required(VERSION 3.21)
project(t1)

set(CMAKE_CXX_STANDARD 14)

include_directories(domain)
include_directories(utils)
include_directories(repository)
include_directories(ui)
include_directories(controller)
include_directories(app)

add_executable(t1
        domain/School.cpp
        utils/utils.cpp
        repository/SchoolRepository.cpp domain/AppException.cpp domain/AppException.h controller/SchoolController.cpp controller/SchoolController.h ui/UI.cpp ui/UI.h app/main.cpp tests/AppTests.cpp tests/AppTests.h)
