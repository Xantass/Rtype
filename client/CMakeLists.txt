cmake_minimum_required(VERSION 3.0)

project(r-type_client)

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++17")

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

include_directories("./inc/" "../ECS/inc/" "./../ECS/inc/systems/" "./../ECS/inc/components/" ${Boost_INCLUDE_DIR})

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

target_link_libraries(r-type_client ${Boost_LIBRARIES})
