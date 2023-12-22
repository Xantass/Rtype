cmake_minimum_required(VERSION 3.16.3)

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

include_directories("./inc/" "../ECS/inc/" "./../ECS/inc/systems/" "./../ECS/inc/components/")
# # Include raylib
# find_package(raylib CONFIG REQUIRED PATHS ${raylib_DIR}/lib64/cmake/raylib/)


# Your project source files
add_executable(r-type_client
    src/Main.cpp
    src/Client.cpp
    )

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
target_link_libraries(r-type_client PRIVATE asio)

# Link your project with raylib
# target_link_libraries(r-type_client PRIVATE ${raylib_LIBRARIES})
# target_include_directories(r-type_client PRIVATE ${raylib_INCLUDE_DIRS})