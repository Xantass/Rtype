cmake_minimum_required(VERSION 3.0)

project(r-type_server)

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++17")

include_directories("./inc/")  # Chemin vers le répertoire des fichiers .hpp

# Configuration des sources de votre projet
set(SOURCES
    src/Server.cpp
    src/main.cpp
)

# Configuration de l'exécutable
add_executable(r-type_server ${SOURCES})
