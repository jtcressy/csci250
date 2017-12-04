cmake_minimum_required(VERSION 3.8)
project(GraphHomework)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp graph.cpp graph.h)
add_executable(GraphHomework ${SOURCE_FILES} graph.cpp graph.h)