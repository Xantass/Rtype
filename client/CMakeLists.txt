cmake_minimum_required(VERSION 3.0)

project(r-type_client)

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++17")

add_executable(r-type_client
    src/ClientMain.cpp
    inc/ClientMain.hpp
    )
