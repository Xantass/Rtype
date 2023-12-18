cmake_minimum_required(VERSION 3.21)

project(r-type_client)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
FetchContent_Declare(
  asiocmake
  GIT_REPOSITORY "https://github.com/OlivierLDff/asio.cmake"
  GIT_TAG        "main"
)
FetchContent_MakeAvailable(asiocmake)

include_directories("./inc/" "../ECS/inc/" "./../ECS/inc/systems/" "./../ECS/inc/components/")

add_executable(r-type_client
    src/ClientMain.cpp

    
    ../ECS/src/systems/PhysicSystem.cpp
    ../ECS/src/systems/NetworkClientSystem.cpp
    ../ECS/src/EntityManager.cpp
    ../ECS/src/ComponentArray.cpp
    ../ECS/src/ComponentManager.cpp
    ../ECS/src/SystemManager.cpp
    ../ECS/src/Coordinator.cpp
    )

target_link_libraries(r-type_client PRIVATE asio)
