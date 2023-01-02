cmake_minimum_required(VERSION 3.16)
project(wordle-analyzer)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -static-libstdc++")

add_executable(wordle-analyzer
        main.cpp
        threaded_analysis.cpp threaded_analysis.h fast_read.h fast_read.cpp)