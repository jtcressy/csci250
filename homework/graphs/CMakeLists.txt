cmake_minimum_required(VERSION 3.8)
project(graphs)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp Graph.cpp Graph.h)
add_executable(graphs ${SOURCE_FILES})