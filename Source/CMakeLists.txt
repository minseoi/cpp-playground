cmake_minimum_required(VERSION 3.29)
project(cpp-boilerplate)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 20)

add_executable(
        cpp-boilerplate
        main.cpp
        Actor/Actor.cpp
        Actor/Actor.h
        Math/Vector.hpp
        Math/Math.cpp
        Math/Math.h
)
