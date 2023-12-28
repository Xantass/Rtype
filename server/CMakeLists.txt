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

project(r-type_server)

include_directories("./inc/" "./../ECS/inc/" "./../ECS/inc/systems/" "./../ECS/inc/components/")

set(SOURCES
    src/main.cpp
    src/room.cpp
    src/Client.cpp

    ../ECS/src/systems/PhysicSystem.cpp
    ../ECS/src/systems/NetworkServerSystem.cpp
    ../ECS/src/systems/NetworkRoomSystem.cpp
    ../ECS/src/EntityManager.cpp
    ../ECS/src/ComponentArray.cpp
    ../ECS/src/ComponentManager.cpp
    ../ECS/src/SystemManager.cpp
    ../ECS/src/Coordinator.cpp
)

add_executable(r-type_server ${SOURCES})

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
