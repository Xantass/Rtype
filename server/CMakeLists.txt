cmake_minimum_required(VERSION 3.0)

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
    src/Server.cpp
    src/main.cpp
    src/RoomManager.cpp
    src/Client.cpp

    ../ECS/src/systems/PhysicSystem.cpp
    ../ECS/src/systems/NetworkServerSystem.cpp
    ../ECS/src/EntityManager.cpp
    ../ECS/src/ComponentArray.cpp
    ../ECS/src/ComponentManager.cpp
    ../ECS/src/SystemManager.cpp
    ../ECS/src/Coordinator.cpp
)

add_executable(r-type_server ${SOURCES})

target_link_libraries(r-type_server PRIVATE asio)

if(WIN32)
    target_link_libraries(r-type_server Ws2_32.lib)
endif()

if(MSVC)
  add_compile_options(/Wv:17)
endif()

if (APPLE AND UNIX)
    SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++17")
endif()

if(UNIX AND NOT APPLE)
    target_compile_options(r-type_server PRIVATE -std=c++17 -Wall -Wextra -O3)
    find_package(Threads REQUIRED)
    target_link_libraries(r-type_server Threads::Threads)
endif()
