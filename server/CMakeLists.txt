cmake_minimum_required(VERSION 3.16.3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
  asiocmake
  GIT_REPOSITORY "https://github.com/OlivierLDff/asio.cmake"
  GIT_TAG        "main"
)
FetchContent_MakeAvailable(asiocmake)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
    GIT_TAG "master"
    GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(raylib)

project(r-type_server)

include_directories("./inc/" "./../ECS/inc/" "./../ECS/inc/systems/" "./../ECS/inc/components/")

set(SOURCES
    src/Server.cpp
    src/main.cpp
    src/RoomManager.cpp
    src/Client.cpp
)

add_executable(r-type_server ${SOURCES})


target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

if(WIN32)
    target_link_libraries(r-type_server PRIVATE Ws2_32.lib asio)
endif()

if(MSVC)
  add_compile_options(/Wv:17)
endif()

if (APPLE AND UNIX)
    SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++20")
    target_link_libraries(r-type_server PRIVATE asio)
endif()

if(UNIX AND NOT APPLE)
    target_compile_options(r-type_server PRIVATE -std=c++2a -Wall -Wextra -O3)
    find_package(Threads REQUIRED)
    target_link_libraries(r-type_server PRIVATE Threads::Threads asio)
endif()
