cmake_minimum_required(VERSION 3.0)

project(r-type_client)

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++17")

include_directories("./inc/")
include_directories("../ECS/inc/")

add_executable(r-type_client
    src/ClientMain.cpp

    
    ../ECS/src/systems/PhysicSystem.cpp
    ../ECS/src/systems/PhysicSystem.cpp
    ../ECS/src/EntityManager.cpp
    ../ECS/src/ComponentArray.cpp
    ../ECS/src/ComponentManager.cpp
    ../ECS/src/SystemManager.cpp
    ../ECS/src/Coordinator.cpp
    )
