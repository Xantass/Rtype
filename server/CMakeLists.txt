cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Spécifiez le chemin vers vcpkg
set(VCPKG_ROOT "${CMAKE_CURRENT_BINARY_DIR}/vcpkg") # Remplacez par votre chemin absolu vers vcpkg
set(Boost_INCLUDE_DIR "${VCPKG_ROOT}/installed/arm64-osx/include/") # Remplacez par votre chemin absolu vers vcpkg

# Assurez-vous que vcpkg a été correctement installé
if(NOT EXISTS "${VCPKG_ROOT}/vcpkg")
    message("Clonage de Vcpkg...")
    execute_process(
        COMMAND git clone https://github.com/microsoft/vcpkg.git
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
    execute_process(
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/vcpkg/bootstrap-vcpkg.sh
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/vcpkg
    )
endif()

# Installation d'Asio et Interprocess de Boost via vcpkg
execute_process(
    COMMAND ${VCPKG_ROOT}/vcpkg install boost-asio boost-interprocess
)

set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

project(r-type_server)

include_directories("./inc/" ${Boost_INCLUDE_DIR} "./../ECS/inc/" "./../ECS/inc/systems/" "./../ECS/inc/components/")

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

target_link_libraries(r-type_server ${Boost_LIBRARIES})

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
