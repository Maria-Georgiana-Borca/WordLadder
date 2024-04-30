cmake_minimum_required(VERSION 3.24)
project(WordLadder)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(WordLadder
        Graph.h Test.cpp automaticMode.h automaticMode.cpp playMode.cpp)
