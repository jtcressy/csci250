cmake_minimum_required(VERSION 3.8)
project(untitled)

set(CMAKE_CXX_STANDARD 17)

set(TREE_SOURCE homework/recursive_btree/main.cpp)
add_executable(recursive_btree ${TREE_SOURCE})

set(LIST_SOURCE homework/recursive_linklist/main.cpp)
add_executable(recursive_linklist ${LIST_SOURCE})

