cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(r-type_server)

include_directories("./inc/")

set(SOURCES
    src/Server.cpp
    src/main.cpp
)

add_executable(r-type_server ${SOURCES})

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
endif()
