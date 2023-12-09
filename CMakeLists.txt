cmake_minimum_required(VERSION 3.10)

# Nom du projet
project(LeLabyrinthe)

# Inclure SDL2
find_package(SDL2 REQUIRED)

# Inclure les fichiers d'en-tête
include_directories(${SDL2_INCLUDE_DIRS} ./Map ./Player ./Render ./Tscreen)

# Ajouter l'exécutable
add_executable(LeLabyrinthe main.c Map/map.c Player/player.c Render/render.c Tscreen/tscreen.c)

# Lier avec SDL2 et la bibliothèque mathématique
target_link_libraries(LeLabyrinthe ${SDL2_LIBRARIES} m)
