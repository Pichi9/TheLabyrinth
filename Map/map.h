#ifndef MAP_H
#define MAP_H

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include "../constantes.h"

typedef struct 
{
	int map[MAP_HEIGHT][MAP_WIDTH];
}GameMap;


// Fonction qui crée la carte à partir du fichier map.txt
GameMap* CreateMap(const char *filename);


// Fonction qui libère toute la mémoire que la carte occupe
void freeMap(GameMap *map);


// Fonction qui dit si c'est un mur 
int isWall(GameMap *map, int x, int y);


// Fonction qui vdit si c'est position est la sortie du labyrinthes
int end(GameMap *map, int x, int y);

#endif