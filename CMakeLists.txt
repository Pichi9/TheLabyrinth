cmake_minimum_required(VERSION 3.0)
project(LeLabyrinthe)

# Configuration des sources pour le projet
set(SOURCES 
    Render/render.h
    Render/render.c
    Map/map.h
    Map/map.c
    main.c
    constantes.h
)

# Recherche des packages SDL2 et SDL2_image
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

# Inclure les répertoires d'en-tête SDL2 et SDL2_image
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

# Création de l'exécutable à partir des fichiers sources
add_executable(LeLabyrinthe ${SOURCES})

# Liens avec les bibliothèques SDL2 et SDL2_image
target_link_libraries(LeLabyrinthe ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

# Copier les fichiers de ressources (textures, etc.) vers le dossier de build
file(COPY Textures DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Déplacer l'exécutable vers le répertoire LeLabyrinthe
set_target_properties(LeLabyrinthe PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)
