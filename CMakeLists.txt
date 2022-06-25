cmake_minimum_required(VERSION 3.16)
project(wordle-analyzer)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_executable(wordle-analyzer
        main.cpp
        analysis.cpp
        analysis.h
        )