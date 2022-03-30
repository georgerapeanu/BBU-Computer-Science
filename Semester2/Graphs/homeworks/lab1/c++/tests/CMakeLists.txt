project(c___tests)

include_directories(../)

add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


add_executable(c___tests
        ../Graph.cpp
        ./graph_tests.cpp)

target_link_libraries(c___tests gtest gtest_main)
