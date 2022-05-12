cmake_minimum_required(VERSION 3.20)
project(lab6-finally)

add_subdirectory(lib/googletest-main)
include_directories(lib/googletest-main/googletest/include)
include_directories(lib/googletest-main/googlemock/include)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab6-finally main.cpp Tests/AVLTree.h Tests/test.cpp)
target_link_libraries(lab6-finally gtest gtest_main)
