cmake_minimum_required(VERSION 3.21)
project(t2_georgerapeanu_1)

set(CMAKE_CXX_STANDARD 14)

include_directories(domain)
include_directories(service)
include_directories(UI)

add_executable(t2_georgerapeanu_1
        domain/Engine.cpp
        domain/ElectricEngine.cpp domain/TurboEngine.cpp
        domain/TurboEngine.h domain/AppException.cpp domain/AppException.h
        domain/Car.cpp domain/Car.h service/Service.cpp service/Service.h UI/UI.cpp UI/UI.h main.cpp)
