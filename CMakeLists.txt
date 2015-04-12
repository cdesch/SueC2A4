cmake_minimum_required(VERSION 3.1)
project(SueC2A4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(SueC2A4 ${SOURCE_FILES} date.hpp person.hpp state.h list.hpp listNode.hpp database.hpp tree.hpp treeNode.hpp test_database.hpp)