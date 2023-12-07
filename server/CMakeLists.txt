cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(r-type_server)

include_directories("./inc/")  # Chemin vers le répertoire des fichiers .hpp

# Configuration des sources de votre projet
set(SOURCES
    src/Server.cpp
    src/main.cpp
)

# Configuration de l'exécutable
add_executable(r-type_server ${SOURCES})

# Configuration spécifique à Windows
if(WIN32)
    # Ajoutez ici les bibliothèques spécifiques à Windows si nécessaire
endif()

if(MSVC)
  add_compile_options(/Wv:17)
endif()

if (APPLE AND UNIX)
    SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++17")
endif()

# Configuration spécifique à Linux
if(UNIX AND NOT APPLE)
    target_compile_options(pbrain-gomoku-ai PRIVATE -std=c++17 -Wall -Wextra -O3)
endif()
