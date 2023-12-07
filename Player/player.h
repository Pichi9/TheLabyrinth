#ifndef PLAYER_H
#define PLAYER_H


#include <SDL.h>
#include <SDL_image.h>
#include "../constantes.h"

typedef struct 
{
	float x; 
	float y;
	float dirX;
	float dirY;
	float angle;
}Player;

// Fonction qui met à jour les variables d'angle en radian
void fixDir(Player *p);

// Fonction qui initialise le joueur
void initPlayer(Player *p);

// Fonction qui libère toute la mémoire que la carte occupe
void freePlayer(Player *p);

// Fonction qui gère l'angle du joueur
void anglePlayer(Player *p);



#endif