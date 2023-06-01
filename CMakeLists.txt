cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
set (CMAKE_CXX_COMPILER "g++")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11")
project(shared_ptr LANGUAGES CXX)

add_executable(shared_ptr test.cpp)
