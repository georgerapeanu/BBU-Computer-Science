project(a8_9_georgerapeanu_tests)

include_directories(../include)
include_directories(../include/domain)
include_directories(../include/repository)
include_directories(../include/controller)
include_directories(../include/ui)

add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


add_executable(a8_9_georgerapeanu_tests
        ../src/domain/Exceptions.cpp
        ../src/domain/Movie.cpp
        ../src/repository/MemoryRepository.cpp
        ../src/controller/MovieController.cpp
        ../src/ui/UI.cpp
        domain/MovieTests.cpp
        repository/MemoryRepositoryTests.cpp
        controller/MovieControllerTests.cpp
        ../src/repository/FileRepository.cpp
        ../src/domain/MovieValidator.cpp
        ../src/repository/CSVWatchlist.cpp
        ../src/repository/HTMLWatchlist.cpp
        ../src/repository/MemoryWatchlist.cpp
        repository/FileRepositoryTests.cpp
        repository/HTMLWatchlistTests.cpp repository/CSVWatchlistTests.cpp repository/MemoryWatchlistTests.cpp)

target_link_libraries(a8_9_georgerapeanu_tests gtest gtest_main)
