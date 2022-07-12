project(a5_6_georgerapeanu_tests)

include_directories(../include)
include_directories(../include/domain)
include_directories(../include/repository)
include_directories(../include/controller)
include_directories(../include/ui)

add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


add_executable(a5_6_georgerapeanu_tests
        ../src/domain/DynamicVector.cpp
        ../src/domain/Exceptions.cpp
        ../src/domain/Movie.cpp
        ../src/repository/Repository.cpp
        ../src/controller/MovieController.cpp
        ../src/ui/UI.cpp
        domain/MovieTests.cpp
        domain/DynamicVectorTests.cpp
        repository/RepositoryTests.cpp controller/MovieControllerTests.cpp)

target_link_libraries(a5_6_georgerapeanu_tests gtest gtest_main)
