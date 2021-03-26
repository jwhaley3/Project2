cmake_minimum_required(VERSION 2.8)
project(untitled)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_STANDARD 14)

add_executable(untitled main.cpp defn.h bst.cpp prime.cpp hash.cpp)