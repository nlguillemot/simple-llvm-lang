cmake_minimum_required(VERSION 2.8)

project(simple)

if(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

add_executable(simple main.cpp)
