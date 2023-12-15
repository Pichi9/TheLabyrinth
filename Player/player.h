#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../constantes.h"
#include "../Map/map.h"

typedef struct 
{
	float x; 
	float y;
	float dirX;
	float dirY;
	float angle;
}Player;

// Fonction
void initSpawnCoords(Player *p, GameMap *m);

// Fonction qui met à jour les variables d'angle en radian
void fixDir(Player *p);

// Fonction qui initialise le joueur
void initPlayer(Player *p, GameMap *m);

// Fonction qui libère toute la mémoire que la carte occupe
void freePlayer(Player *p);

// Fonction qui gère l'angle du joueur
void anglePlayer(Player *p);



#endif