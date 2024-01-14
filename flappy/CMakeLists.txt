cmake_minimum_required(VERSION 3.16.3)

project(flappy-bird)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# Adding Raylib
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games

FetchContent_Declare(
    raylib
    GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
    GIT_TAG "master"
    GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(raylib)

include_directories("./inc/" "./../ECS/" "../ECS/inc/" "./../ECS/inc/systems/" "./../ECS/inc/components/")

# Your project source files
add_executable(flappy-bird
    src/Main.cpp
    src/Creator.cpp
    )

if(WIN32)
    target_link_libraries(flappy-bird PRIVATE Ws2_32.lib raylib)
endif()

if(MSVC)
  add_compile_options(/Wv:17)
endif()

if (APPLE AND UNIX)
    SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++20")
    target_link_libraries(flappy-bird PRIVATE raylib)
endif()

if(UNIX AND NOT APPLE)
    target_compile_options(flappy-bird PRIVATE -std=c++2a -Wall -Wextra -O3 -g3)
    target_link_libraries(flappy-bird PRIVATE raylib)
endif()

# Link your project with raylib
target_link_libraries(flappy-bird PRIVATE ${raylib_LIBRARIES})
target_include_directories(flappy-bird PRIVATE ${raylib_INCLUDE_DIRS})