cmake_minimum_required(VERSION 3.0)

project(r-type_client)

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++17")


include(ExternalProject)

# Explicitly set the path to raylib
# set(raylib_DIR ${CMAKE_BINARY_DIR}/raylib/install/)

# Adding Raylib
include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games

FetchContent_Declare(
    raylib
    GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
    GIT_TAG "master"
    GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(raylib)

include_directories("./inc/")
include_directories("../ECS/inc/")
# # Include raylib
# find_package(raylib CONFIG REQUIRED PATHS ${raylib_DIR}/lib64/cmake/raylib/)


# Your project source files
add_executable(r-type_client
    src/ClientMain.cpp


    ../ECS/src/systems/PhysicSystem.cpp
    ../ECS/src/systems/GraphicalSystem.cpp
    ../ECS/src/EntityManager.cpp
    ../ECS/src/ComponentArray.cpp
    ../ECS/src/ComponentManager.cpp
    ../ECS/src/SystemManager.cpp
    ../ECS/src/Coordinator.cpp
    )

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# Link your project with raylib
# target_link_libraries(r-type_client PRIVATE ${raylib_LIBRARIES})
# target_include_directories(r-type_client PRIVATE ${raylib_INCLUDE_DIRS})